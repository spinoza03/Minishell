/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:25 by ilallali          #+#    #+#             */
/*   Updated: 2025/05/31 16:37:48 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void    execute_this_one_command(char **args, char **envp)
{
    pid_t   pid;

    if (!args || !args[0])
        return;
    pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork");
        return;
    }
    else if (pid == 0)
    {
        if (execve(args[0], args, envp) == -1)
        {
            perror("minishell");
            exit(EXIT_FAILURE);
        }
    }
    else // Parent process
    {
        int child_status;
        if (waitpid(pid, &child_status, 0) == -1)
        {
            perror("minishell: waitpid");
        }
    }
}
