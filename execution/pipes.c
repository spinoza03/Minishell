/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:51:18 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/30 18:30:12 by ilallali         ###   ########.fr       */
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

// Helper 3: Handles logic for a forked child process in a pipe.
static void    child_in_pipe(t_cmd *cmd, t_shell *shell, char **envp,
                            int in_fd, int pipe_fds[2])
{
    int    out_fd;

    if (cmd->next)
        out_fd = pipe_fds[1];
    else
        out_fd = STDOUT_FILENO;
    // The child needs its own signal handlers
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    // Pipe redirection
    if (in_fd != STDIN_FILENO)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    if (out_fd != STDOUT_FILENO)
    {
        close(pipe_fds[0]);
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
    // The controller handles file redirections and runs the command
    exit(execute_command_controller(cmd, shell, envp));
}

// Helper 4: Waits for all children in the pipeline to finish.
static int    wait_for_pipeline(pid_t last_pid, int cmd_count)
{
    int    status;
    int    last_status;

    last_status = 0;
    while (cmd_count > 0)
    {
        if (wait(&status) == last_pid)
            last_status = status;
        cmd_count--;
    }
    // Interpret and return the status of the LAST command
    if (WIFEXITED(last_status))
        return (WEXITSTATUS(last_status));
    else if (WIFSIGNALED(last_status))
        return (128 + WTERMSIG(last_status));
    return (last_status);
}

// --- MAIN EXECUTION FUNCTION ---

// The main `execute_pipeline` function, now short and clean.
int    execute_pipeline(t_cmd *cmd_list, t_shell *shell,
                        char **original_envp)
{
    pid_t           last_pid;
    int             pipe_fds[2];
    int             in_fd;
    t_builtin_id    builtin_id;

    if (!cmd_list)
        return (0);
    // Special case for a single, parent-safe built-in command
    if (cmd_list->next == NULL)
    {
        builtin_id = get_builtin_id(cmd_list->args[0]);
        if (is_parent_builtin(builtin_id))
        {
            int original_fds[2];
            apply_redirections(cmd_list, original_fds);
            shell->last_exit_status = execute_builtin_command(builtin_id, cmd_list, shell);
            restore_redirections(original_fds);
            return (shell->last_exit_status);
        }
    }
    // All other cases (pipelines or single commands that need forking)
    in_fd = STDIN_FILENO;
    last_pid = -1;
    shell->child_pid = 1; // Set flag: children are running
    while (cmd_list)
    {
        if (cmd_list->next && pipe(pipe_fds) == -1)
            return (perror("minishell: pipe"), 1);
        last_pid = fork();
        if (last_pid < 0)
            return (perror("minishell: fork"), 1);
        if (last_pid == 0)
            child_in_pipe(cmd_list, shell, original_envp, in_fd, pipe_fds);
        if (in_fd != STDIN_FILENO)
            close(in_fd);
        if (cmd_list->next)
        {
            close(pipe_fds[1]);
            in_fd = pipe_fds[0];
        }
        cmd_list = cmd_list->next;
    }
    shell->last_exit_status = wait_for_pipeline(last_pid, count_commands(cmd_list));
    shell->child_pid = 0; // Reset flag: children are done
    return (shell->last_exit_status);
}
