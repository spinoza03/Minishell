/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:12:00 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/06 16:07:23 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

// static char	*get_current_directory()
// {
// 	char	*curr_dir;

// 	curr_dir = (char *)malloc(sizeof(char) *1024);
// 	if(!curr_dir)
// 		return (NULL);
// 	if(getcwd(curr_dir, 1024) == NULL)
// 	{
// 		perror("minishell: cd: getcwd error");
// 		free(curr_dir);
// 		return (NULL);
// 	}
// 	return (curr_dir);
// }
// static void	update_pwd_env(t_env_copy **env_list, char *old_pwd)
// {
// 	char	*new_pwd;
	
// 	if(old_pwd)
// 	{
// 		set_env_value(env_list, "OLDPWD", old_pwd);
// 		free(old_pwd);
// 	}
// 	new_pwd = get_current_directory();
// 	if(new_pwd)
// 	{
// 		set_env_value(env_list, "PWD", new_pwd);
// 		free(new_pwd);
// 	}
// }

int exec_cd(t_cmd *command, t_shell *shell)
{
    char *old_pwd;
    char *new_pwd;

    if (!command->args[1])
        return (0);
    if (command->args[2] != NULL)
    {
        write(2, "minishell: cd: too many arguments\n", 34);
        return (1);
    }
    old_pwd = get_env_value(*(shell->env_list), "PWD");
    if (chdir(command->args[1]) != 0)
    {
        perror(command->args[1]);
        return (1);
    }
    if (old_pwd)
        set_env_value(shell->env_list, "OLDPWD", old_pwd);
    new_pwd = getcwd(NULL, 0);
    if (new_pwd)
    {
        set_env_value(shell->env_list, "PWD", new_pwd);
        free(new_pwd);
    }
    return (0);
}
