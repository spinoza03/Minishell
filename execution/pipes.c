/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:51:18 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/06 16:09:46 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

// Helper 1: Checks if a built-in must run in the parent process.
static int is_parent_builtin(t_builtin_id id)
{
    return (id == BUILTIN_CD || id == BUILTIN_EXPORT ||
            id == BUILTIN_UNSET || id == BUILTIN_EXIT);
}

// Helper 2: Counts commands in a pipeline.
static int count_commands(t_cmd *cmd_list)
{
    int count;

    count = 0;
    while (cmd_list)
    {
        count++;
        cmd_list = cmd_list->next;
    }
    return (count);
}

// Helper 3: Handles logic for the parent process inside the pipeline loop.
static void    parent_setup_pipes(int *in_fd, int pipe_fds[2], t_cmd *cmd)
{
    if (*in_fd != STDIN_FILENO)
        close(*in_fd);
    if (cmd->next)
    {
        close(pipe_fds[1]);
        *in_fd = pipe_fds[0];
    }
}

// Helper 4: Waits for all children in the pipeline to finish.
static int    wait_for_pipeline(pid_t last_pid, int cmd_count)
{
    int    status;
    int    last_status;
    pid_t  waited_pid;

    last_status = 0;
    while (cmd_count > 0)
    {
        waited_pid = wait(&status);
        if (waited_pid == -1)
        {
            if (errno == EINTR) // Handle interrupted system calls
                continue;
            break;
        }
        if (waited_pid == last_pid)
            last_status = status;
        cmd_count--;
    }
    if (WIFEXITED(last_status))
        return (WEXITSTATUS(last_status));
    else if (WIFSIGNALED(last_status))
    {
        // --- ADD THIS CHECK ---
        if (WTERMSIG(last_status) == SIGQUIT)
            write(2, "Quit (core dumped)\n", 20);
        // --- END OF ADDED CHECK ---
        return (128 + WTERMSIG(last_status));
    }
    return (last_status);
}

static void    child_in_pipe(t_cmd *cmd, t_shell *shell, char **envp,
                            int in_fd, int pipe_fds[2])
{
    int    out_fd;

    // This block determines where the output of this command should go.
    // If there is another command after this one, send output to the pipe.
    if (cmd->next)
        out_fd = pipe_fds[1];
    else // Otherwise, this is the last command, so send output to the screen.
        out_fd = STDOUT_FILENO;

    // --- Set up I/O for the child ---

    // 1. Reset signals to default behavior for the child process.
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    // 2. Redirect standard input if it's coming from a previous pipe.
    if (in_fd != STDIN_FILENO)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    // 3. Redirect standard output if it's going to the next pipe.
    if (out_fd != STDOUT_FILENO)
    {
        close(pipe_fds[0]); // Child doesn't read from its own output pipe.
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }

    // 4. Now that pipes are set up, run the command controller.
    //    The controller will handle file redirections (like > file.txt)
    //    and then execute the command (built-in or external).
    // 5. The child process exits with the status of the command.
    exit(execute_command_controller(cmd, shell, envp));
}

// The Main `execute_pipeline` Function
int    execute_pipeline(t_cmd *cmd_list, t_shell *shell,
                        char **original_envp)
{
    pid_t           last_pid;
    int             pipe_fds[2];
    int             in_fd;
    t_cmd           *head;
    t_builtin_id    builtin_id;

    head = cmd_list;
    builtin_id = get_builtin_id(cmd_list->args[0]);
    // Special case for a single, parent-safe built-in command
    if (cmd_list->next == NULL && is_parent_builtin(builtin_id))
    {
        int original_fds[2];
        apply_redirections(cmd_list, original_fds);
        shell->last_exit_status = execute_builtin_command(builtin_id, cmd_list, shell);
        restore_redirections(original_fds);
        return (shell->last_exit_status);
    }
    // All other cases: pipelines or single commands that must be forked
    in_fd = STDIN_FILENO;
    last_pid = -1;
    shell->child_pid = 1; // Set flag that children are running
    while (cmd_list)
    {
        if (cmd_list->next && pipe(pipe_fds) == -1)
            return (perror("minishell: pipe"), 1);
        last_pid = fork();
        if (last_pid < 0)
            return (perror("minishell: fork"), 1);
        if (last_pid == 0)
            child_in_pipe(cmd_list, shell, original_envp, in_fd, pipe_fds);
        parent_setup_pipes(&in_fd, pipe_fds, cmd_list);
        cmd_list = cmd_list->next;
    }
    shell->last_exit_status = wait_for_pipeline(last_pid, count_commands(head));
    shell->child_pid = 0; // Reset flag after all children are done
    return (shell->last_exit_status);
}
