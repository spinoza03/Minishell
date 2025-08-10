/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_enset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:55:58 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/10 14:48:12 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	exec_unset(t_cmd *command, t_shell *shell)
{
	int	i;

	i = 1;
	while (command->args[i])
	{
		env_lstdel_one(shell->env_list, command->args[i]);
		i++;
	}
	return (0);
}
