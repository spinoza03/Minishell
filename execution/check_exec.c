/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:47:25 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/10 18:22:28 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	handle_external_command(t_cmd *command, t_shell *shell,
									char **original_envp)
{
	char	*executable_path;

	executable_path = resolve_command_path(command->args[0],
			*(shell->env_list));
	if (executable_path)
	{
		execve(executable_path, command->args, original_envp);
		free(executable_path);
		write(2, "minishell: ", 11);
		perror(command->args[0]);
		exit(126);
	}
	else
	{
		write(2, "minishell: ", 11);
		write(2, command->args[0], ft_strlen(command->args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
}

int	execute_command_controller(t_cmd *command, t_shell *shell,
									char **original_envp)
{
	t_builtin_id	builtin_id;
	int				dummy_fds[2];

	if (apply_redirections(command, dummy_fds) != 0)
		exit(1);
	if (!command->args || !command->args[0])
		exit(0);
	builtin_id = get_builtin_id(command->args[0]);
	if (builtin_id != NOT_A_BUILTIN_ID)
		return (execute_builtin_command(builtin_id, command, shell));
	else
		handle_external_command(command, shell, original_envp);
	return (1);
}
