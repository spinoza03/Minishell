/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_enset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:55:58 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/14 17:03:06 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	exec_unset(t_cmd *command, t_env_copy **env_list)
{
	int	i;

	i = 0;
	while (command->args[i])
	{
		env_lstdel_one(env_list, command->args[i]);
		i++;
	}
	return (0);
}