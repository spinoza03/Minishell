/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:04:24 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/10 14:51:07 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	exec_env(t_cmd *command, t_shell *shell)
{
	t_env_copy	*current;

	if (command->args[1] != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(command->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	current = *(shell->env_list);
	while (current)
	{
		if (current->value)
		{
			write(1, current->key, ft_strlen(current->key));
			write(1, "=", 1);
			write(1, current->value, ft_strlen(current->value));
			write(1, "\n", 1);
		}
		current = current->next;
	}
	return (0);
}
