/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 22:03:44 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/10 00:21:23 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	print_cmd_list_debug(t_cmd *cmd_list);

static void	print_redirs(t_redirs *redir_list)
{
	t_redirs	*current;
	int			i;

	current = redir_list;
	i = 0;
	while (current)
	{
		printf("    -> Redir[%d]: type=%d, filename='%s'\n",
			i, current->type, current->filename);
		current = current->next;
		i++;
	}
}

void	print_cmd_list_debug(t_cmd *cmd_list)
{
	t_cmd	*current_cmd;
	int		i;
	int		j;

	printf("--- DEBUG: Parsed Command List ---\n");
	current_cmd = cmd_list;
	i = 0;
	while (current_cmd)
	{
		printf("  Command[%d]:\n", i);
		if (current_cmd->args)
		{
			j = 0;
			while (current_cmd->args[j])
			{
				printf("    - Arg[%d]: '%s'\n", j, current_cmd->args[j]);
				j++;
			}
		}
		else
			printf("    - Args: (null)\n");
		if (current_cmd->redirs)
			print_redirs(current_cmd->redirs);
		else
			printf("    - Redirs: (none)\n");
		current_cmd = current_cmd->next;
		i++;
	}
	printf("------------------------------------\n");
}