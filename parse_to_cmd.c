/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:46:49 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/06 19:13:37 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_cmd	*new_cmd()
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if(!cmd)
		return NULL;
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return cmd;
}


