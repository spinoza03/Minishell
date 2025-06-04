/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:25 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/04 13:52:32 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h" // Adjust path as needed

int execute_command_controller(t_cmd *command, t_env_copy **env_list,
                                                            char **original_envp)
{
    t_builtin_id    builtin_id;
    int             exit_status;

    exit_status = 1; // Default to error if something unexpected happens.
    if (!command || !command->args || !command->args[0])
    {
        return (1); // Return an error status for an invalid/empty command.
    }
    builtin_id = get_builtin_id(command->args[0]);
    if (builtin_id != NOT_A_BUILTIN_ID)
    {
        exit_status = execute_builtin_command(builtin_id, command, env_list);
    }
    else
    {
		char *resolved_path_debug; // Temporary for debugging
    resolved_path_debug = resolve_command_path_part1(command->args[0], *env_list);
    if (resolved_path_debug) // This will be NULL for now from part1
    {
        // Later: use this path
        // For now, just showing it's called.
        // free(resolved_path_debug); // Important when it actually returns an allocated string
    }
        exit_status = execute_external_command(command, original_envp);
    }
    return (exit_status);
}
