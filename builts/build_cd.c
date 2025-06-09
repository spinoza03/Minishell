/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:12:00 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/09 14:43:58 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static char	*get_current_directory()
{
	char	*curr_dir;

	curr_dir = (char *)malloc(sizeof(char) *1024);
	if(!curr_dir)
		return (NULL);
	if(getcwd(curr_dir, 1024) == NULL)
	{
		perror("minishell: cd: getcwd error");
		free(curr_dir);
		return (NULL);
	}
	return (curr_dir);
}
static void	update_pwd_env(t_env_copy **env_list, char *old_pwd)
{
	char	*new_pwd;
	
	if(old_pwd)
	{
		set_env_value(env_list, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	new_pwd = get_current_directory();
	if(new_pwd)
	{
		set_env_value(env_list, "PWD", new_pwd);
		free(new_pwd);
	}
}

int	exec_cd(t_cmd *command, t_env_copy **env_list)
{
	char	*old_pwd;

	if (!command->args[1])
	{
		chdir("/home");
		return (0);
	}
	old_pwd = get_current_directory();
	if(command->args[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if(chdir(command->args[1]) != 0)
	{
		perror(command->args[1]);
		return (1);	
	}
	update_pwd_env(env_list, old_pwd);
	return (0);
}
