/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:12:00 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/08 13:21:49 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	update_pwd_variables(t_shell *shell)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = get_env_value(*(shell->env_list), "PWD");
	if (old_pwd)
		set_env_value(shell->env_list, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("minishell: cd: error retrieving current directory");
		return (1);
	}
	set_env_value(shell->env_list, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

int	exec_cd(t_cmd *command, t_shell *shell)
{
	char	*path;

	if (command->args[1] && command->args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (!command->args[1])
	{
		path = get_env_value(*(shell->env_list), "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else
		path = command->args[1];
	if (chdir(path) != 0)
	{
		perror(path);
		return (1);
	}
	return (update_pwd_variables(shell));
}
