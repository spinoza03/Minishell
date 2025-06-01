/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:14:40 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/01 18:34:35 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	exec_pwd(t_cmd *cmd)
{
	char pw[1024];

	(void)cmd;
	if(getcwd(pw, sizeof(pw)) != NULL)
	{
		printf("%s\n", pw);
		return (0);
	}
	else
	{
		perror("minishell : pwd");
		return (1);	
	}
}
