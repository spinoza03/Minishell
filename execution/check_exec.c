/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:25 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/13 18:01:17 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h" // Adjust path as needed

int execute_command_controller(t_cmd *command, t_env_copy **env_list,
                                                            char **original_envp)
{
    t_builtin_id    builtin_id;
    int             exit_status;
	char			*executable_path;

    exit_status = 1; // Default to error if something unexpected happens.
    if (!command || !command->args || !command->args[0])
    {
        return (1); // Return an error status for an invalid/empty command.
    }
    builtin_id = get_builtin_id(command->args[0]);
    if (builtin_id != NOT_A_BUILTIN_ID)
		exit_status = execute_builtin_command(builtin_id, command, env_list);
    else // For external commands
	{
		executable_path = resolve_command_path(command->args[0], *env_list);
		if (executable_path)
		{
			// Pass the resolved path and the original command structure
			exit_status = execute_external_command(executable_path, command, original_envp);
			free(executable_path); // Crucial: free the path returned by resolve_command_path
		}
		else
		{
			write(2, "minishell: ", 11);
			if (command->args && command->args[0]) // Check args[0] isn't NULL
				write(2, command->args[0], ft_strlen(command->args[0]));
			write(2, ": command not found\n", 20);
			exit_status = 127;
		}
	}
    return (exit_status);
}
