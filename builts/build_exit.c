/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:19:47 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/10 14:51:39 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	is_valid_long_long(const char *str)
{
	int		i;
	size_t	len;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	len = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		len++;
		i++;
	}
	if (len > 19)
		return (0);
	return (1);
}

int	exec_exit(t_cmd *command, t_shell *shell)
{
	int	exit_code;

	exit_code = shell->last_exit_status;
	write(1, "exit\n", 5);
	if (command->args[1])
	{
		if (is_valid_long_long(command->args[1]))
		{
			if (command->args[2])
			{
				write(2, "minishell: exit: too many arguments\n", 36);
				return (1);
			}
			exit_code = ft_atoi(command->args[1]);
		}
		else
		{
			write(2, "minishell: exit: numeric argument required\n", 43);
			exit_code = 255;
		}
	}
	exit(exit_code);
	return (1);
}
