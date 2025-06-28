/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allali <allali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:51:18 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/27 16:46:11 by allali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

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

static void    child_in_pipe(t_cmd *cmd, t_env_copy **env, char **envp,
                            int in_fd, int pipe_fds[2])
{
    int    out_fd;

    if (cmd->next)
        out_fd = pipe_fds[1];
    else
        out_fd = STDOUT_FILENO;
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
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
    exit(execute_command_controller(cmd, env, envp));
}

// Helper 2: Logic for the parent process *inside* the loop (NEW).
static void    parent_setup_pipes(int *in_fd, int pipe_fds[2], t_cmd *cmd)
{
    // The parent process must close its copy of the pipe ends.
    if (*in_fd != STDIN_FILENO)
        close(*in_fd);
    if (cmd->next)
    {
        close(pipe_fds[1]); // Parent doesn't write to the pipe
        *in_fd = pipe_fds[0]; // Save the read end for the next child
    }
}

// Helper 3: Logic for waiting after the loop (no changes from before).
static int    wait_for_pipeline(pid_t last_pid, int cmd_count)
{
    int    status;
    int    last_status;
    pid_t  waited_pid;

    last_status = 0;
    while (cmd_count > 0)
    {
        waited_pid = wait(&status);
        if (waited_pid == last_pid)
            last_status = status;
        cmd_count--;
    }
    if (WIFEXITED(last_status))
        return (WEXITSTATUS(last_status));
    else if (WIFSIGNALED(last_status))
    {
        if (WTERMSIG(last_status) == SIGQUIT)
            write(2, "Quit (core dumped)\n", 20);
        return (128 + WTERMSIG(last_status));
    }
    return (last_status);
}

// Main `execute_pipeline` function, now short and norm-compliant.
int    execute_pipeline(t_cmd *cmd_list, t_env_copy **env_list,
                        char **original_envp)
{
    pid_t   last_pid;
    int     pipe_fds[2];
    int     in_fd;
    int     cmd_count;

    if (!cmd_list)
        return (0);
    if (cmd_list->next == NULL)
        return (execute_command_controller(cmd_list, env_list, original_envp));
    in_fd = STDIN_FILENO;
    last_pid = -1;
    cmd_count = count_commands(cmd_list); // Assuming you add this small counter helper
    while (cmd_list)
    {
        if (cmd_list->next && pipe(pipe_fds) == -1)
            return (perror("minishell: pipe"), 1);
        last_pid = fork();
        if (last_pid < 0)
            return (perror("minishell: fork"), 1);
        if (last_pid == 0)
            child_in_pipe(cmd_list, env_list, original_envp, in_fd, pipe_fds);
        parent_setup_pipes(&in_fd, pipe_fds, cmd_list);
        cmd_list = cmd_list->next;
    }
    return (wait_for_pipeline(last_pid, cmd_count));
}
