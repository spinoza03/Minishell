/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:47:38 by allali            #+#    #+#             */
/*   Updated: 2025/07/08 13:33:49 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	child_process_execution(const char *exec_path, char **args, char **original_envp)
{
    if (execve(exec_path, args, original_envp))
        exit(127);
}

int parent_process_wait(pid_t pid)
{
    int wstatus;
    int exit_status;

    exit_status = 1;

    if (waitpid(pid, &wstatus, 0) == -1)
        perror("minishell: waitpid");
    else
    {
        if (WIFEXITED(wstatus))
            exit_status = WEXITSTATUS(wstatus);
        else if (WIFSIGNALED(wstatus))
            exit_status = 128 + WTERMSIG(wstatus);
    }
    return (exit_status);
}
