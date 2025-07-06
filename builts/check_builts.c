/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:53 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/06 15:40:54 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

t_builtin_id get_builtin_id(const char *cmd_name)
{
    if (!cmd_name)
        return (NOT_A_BUILTIN_ID);
    if (ft_strcmp(cmd_name, "pwd") == 0)
        return (BUILTIN_PWD);
    else if (ft_strcmp(cmd_name, "echo") == 0)
        return (BUILTIN_ECHO);
    else if (ft_strcmp(cmd_name, "cd") == 0)
        return (BUILTIN_CD);
    else if (ft_strcmp(cmd_name, "export") == 0)
        return (BUILTIN_EXPORT);
    else if (ft_strcmp(cmd_name, "unset") == 0)
        return (BUILTIN_UNSET);
    else if (ft_strcmp(cmd_name, "env") == 0)
        return (BUILTIN_ENV);
    else if (ft_strcmp(cmd_name, "exit") == 0)
        return (BUILTIN_EXIT);
    return (NOT_A_BUILTIN_ID);
}

int execute_builtin_command(t_builtin_id id, t_cmd *command, t_shell *shell)
{
    if (id == BUILTIN_PWD)
        return (exec_pwd(command));
    if (id == BUILTIN_ECHO)
        return (exec_echo(command));
    if (id == BUILTIN_CD)
        return (exec_cd(command, shell));
    if (id == BUILTIN_ENV)
        return (exec_env(command, shell));
    if (id == BUILTIN_EXPORT)
        return (exec_export(command, shell));
    if (id == BUILTIN_UNSET)
        return (exec_unset(command, shell));
    if (id == BUILTIN_EXIT)
        return (exec_exit(command, shell));
    return (1);
}
