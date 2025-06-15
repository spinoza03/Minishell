/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:53 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/14 19:30:07 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

t_builtin_id get_builtin_id(const char *cmd_name)
{
    if (!cmd_name)
        return (NOT_A_BUILTIN_ID); // Handle NULL input
    if (ft_strcmp(cmd_name, "pwd") == 0)
        return (BUILTIN_PWD);
    // Add other built-ins here as you implement them:
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

int execute_builtin_command(t_builtin_id id, t_cmd *command, t_env_copy **env_list)
{
	int exit_status;

	exit_status = 1; // Default error status if id is not handled
	if (id == BUILTIN_PWD)
		exit_status = exec_pwd(command);
	else if (id == BUILTIN_ECHO)
	exit_status = exec_echo(command);
	else if (id == BUILTIN_CD)
	exit_status = exec_cd(command, env_list);
	else if (id == BUILTIN_ENV)
	exit_status = exec_env(command, env_list);
	else if (id == BUILTIN_EXPORT)
	exit_status = exec_export(command, env_list);
	else if (id == BUILTIN_UNSET)
	exit_status = exec_unset(command, env_list);
	else if (id == BUILTIN_EXIT)
	exit_status = exec_exit(command, env_list);
	else if (id == NOT_A_BUILTIN_ID) 
		exit_status = 127;
	if (id != BUILTIN_CD && id != BUILTIN_EXPORT && id != BUILTIN_UNSET
		&& id != BUILTIN_ENV && id != BUILTIN_EXIT)
		(void)env_list;
	return (exit_status);
}
