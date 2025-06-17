/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:25 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/16 21:37:19 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int handle_external_command(t_cmd *command, t_env_copy **env_list,
                                                        char **original_envp)
{
    char    *executable_path;
    int     exit_status;

    executable_path = resolve_command_path(command->args[0], *env_list);
    if (executable_path)
    {
        exit_status = execute_external_command(executable_path, command, original_envp);
        free(executable_path);
    }
    else
    {
        write(2, "minishell: ", 11);
        write(2, command->args[0], ft_strlen(command->args[0]));
        write(2, ": command not found\n", 20);
        exit_status = 127;
    }
    return (exit_status);
}

int execute_command_controller(t_cmd *command, t_env_copy **env_list,
                                                            char **original_envp)
{
    t_builtin_id    builtin_id;
    int             exit_status;
    int             original_fds[2];

    exit_status = 1;
    if (!command)
        return (exit_status);
    if (apply_redirections(command, original_fds) != 0)
        return (1);
    if (command->args && command->args[0])
    {
        builtin_id = get_builtin_id(command->args[0]);
        if (builtin_id != NOT_A_BUILTIN_ID)
            exit_status = execute_builtin_command(builtin_id, command, env_list);
        else
            exit_status = handle_external_command(command, env_list, original_envp);
    }
    else
        exit_status = 0;
    restore_redirections(original_fds);

    return (exit_status);
}
