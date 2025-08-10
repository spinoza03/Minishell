/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:24:24 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/10 19:16:22 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	is_parent_builtin(t_builtin_id id)
{
	return (id == BUILTIN_CD || id == BUILTIN_EXPORT
		|| id == BUILTIN_UNSET || id == BUILTIN_EXIT);
}

int	count_commands(t_cmd *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

void	parent_setup_pipes(t_fds *fds, t_cmd *cmd)
{
	if (fds->in != STDIN_FILENO)
		close(fds->in);
	if (cmd->next)
	{
		close(fds->pipe[1]);
		fds->in = fds->pipe[0];
	}
}
