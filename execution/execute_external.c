/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:58:23 by allali            #+#    #+#             */
/*   Updated: 2025/07/06 16:24:31 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int execute_external_command(const char *exec_path, t_cmd *command,
                                                    char **original_envp)
{
    pid_t   pid;
    int     exit_status;

    exit_status = 1;
    pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork");
        return (1);
    }
    if (pid == 0)
        child_process_execution(exec_path, command->args, original_envp);
    else
        exit_status = parent_process_wait(pid);
    return (exit_status);
}
