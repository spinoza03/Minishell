/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:56:53 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/01 18:45:12 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

t_builtin_id get_builtin_id(const char *cmd_name)
{
    if (!cmd_name)
        return (NOT_A_BUILTIN_ID); // Handle NULL input
    if (strcmp(cmd_name, "pwd") == 0)
        return (BUILTIN_PWD);
    // Add other built-ins here as you implement them:
    // else if (strcmp(cmd_name, "echo") == 0)
    //     return (BUILTIN_ECHO);
    // else if (strcmp(cmd_name, "cd") == 0)
    //     return (BUILTIN_CD);
    // else if (strcmp(cmd_name, "export") == 0)
    //     return (BUILTIN_EXPORT);
    // else if (strcmp(cmd_name, "unset") == 0)
    //     return (BUILTIN_UNSET);
    // else if (strcmp(cmd_name, "env") == 0)
    //     return (BUILTIN_ENV);
    // else if (strcmp(cmd_name, "exit") == 0)
    //     return (BUILTIN_EXIT);
    return (NOT_A_BUILTIN_ID); // If no match, it's not a recognized built-in
}

int execute_builtin_command(t_builtin_id id, t_cmd *command, t_env_copy **env_list)
{
	int exit_status;

	exit_status = 1; // Default error status if id is not handled
	if (id == BUILTIN_PWD)
		exit_status = exec_pwd(command);
	// else if (id == BUILTIN_ECHO)
	// exit_status = exec_echo(command); // Pass env_list if needed by echo
	// else if (id == BUILTIN_CD)
	// exit_status = exec_cd(command, env_list);
	// else if (id == BUILTIN_ENV)
	// exit_status = exec_env(command, env_list);
	// else if (id == BUILTIN_EXPORT)
	// exit_status = exec_export(command, env_list);
	// else if (id == BUILTIN_UNSET)
	// exit_status = exec_unset(command, env_list);
	// else if (id == BUILTIN_EXIT)
	// exit_status = exec_exit(command);
	else if (id == NOT_A_BUILTIN_ID) // Or if no other 'if' matched
		exit_status = 127; // Command not found (should not happen if called right)
	if (id != BUILTIN_CD && id != BUILTIN_EXPORT && id != BUILTIN_UNSET
		&& id != BUILTIN_ENV && id != BUILTIN_EXIT /* add other env users */)
		(void)env_list;
	return (exit_status);
}
