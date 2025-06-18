/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:51:18 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/17 19:16:05 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void handle_child_process(t_cmd *cmd, t_env_copy **env, char **envp,
                                 int in_fd, int out_fd)
{
    // Redirect input if it's not the first command
    if (in_fd != STDIN_FILENO)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    // Redirect output if it's not the last command
    if (out_fd != STDOUT_FILENO)
    {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }

    // Now, this child process runs the command using our old controller.
    // The controller will handle file redirections (like `> file`) on top
    // of the pipe redirections we just set up.
    // The child will exit with the command's status code.
    exit(execute_command_controller(cmd, env, envp));
}

// This function contains the logic that runs in the parent after forking.
static void handle_parent_process(int *in_fd, int *pipe_fds)
{
    // The parent must close its copy of the pipe ends to avoid issues.
    if (*in_fd != STDIN_FILENO)
        close(*in_fd); // Close the read end from the previous pipe.
    
    // The parent doesn't write to the new pipe, so close the write end.
    close(pipe_fds[1]);
    
    // The read end of the current pipe becomes the input for the next command.
    *in_fd = pipe_fds[0];
}


int execute_pipeline(t_cmd *cmd_list, t_env_copy **env_list, char **original_envp)
{
    int     status;
    pid_t   last_pid;
    int     pipe_fds[2];
    int     in_fd;

    if (!cmd_list)
        return (0);
    if (cmd_list->next == NULL)
        return (execute_command_controller(cmd_list, env_list, original_envp));
    status = 0;
    in_fd = STDIN_FILENO;
    while (cmd_list)
    {
        if (pipe(pipe_fds) == -1)
            perror("minishell: pipe");
        last_pid = fork();
        if (last_pid == -1)
            perror("minishell: fork");
        else if (last_pid == 0) 
            handle_child_process(cmd_list, env_list, original_envp, in_fd,
                                 (cmd_list->next ? pipe_fds[1] : STDOUT_FILENO));
        else
            handle_parent_process(&in_fd, pipe_fds);
        cmd_list = cmd_list->next;
    }
    close(in_fd);
    int i = 0;
    while(wait(&status) > 0)
        i++;
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (status);
}
