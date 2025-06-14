/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:15:19 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/14 15:55:05 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	pars_export_arg(char *arg, char **key, char **value)
{
	char	*equal_sign_pos;

	equal_sign_pos = ft_strchr(arg, '=');
	if (equal_sign_pos == NULL)
	{
		*key = NULL;
		*value = NULL;
		return (1);
	}
	*value = ft_strdup(equal_sign_pos + 1);
	if (!*value)
		return (1);
	*equal_sign_pos = '\0';
	*key = ft_strdup(arg);
	*equal_sign_pos = '=';
	if(!key)
	{
		free(*value);
		*value = NULL;
		return (1);
	}
	return (0);
}

int	exec_export(t_cmd *command, t_env_copy **env_list)
{
	int		i;
	char	*key;
	char	*value;
	int		exit_status;
	
	i = 1;
	exit_status = 0;
	if(!command->args[i])
		return(exec_env(command, env_list));
	while (command->args[i])
	{
		key = NULL;
		value = NULL;
		if (!pars_export_arg(command->args[i], &key, &value))
		{
			set_env_value(env_list, key, value);
			free(key);
			free(value);
		}
		else
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
