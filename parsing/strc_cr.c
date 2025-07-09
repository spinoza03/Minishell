/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strc_cr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:14:48 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/09 23:31:31 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

// t_cmd	*init_new_cmd(t_ptr **head)
// {
// 	t_cmd	*cmd;

// 	cmd = ft_mall(head, sizeof(t_cmd));
// 	cmd->args = NULL;
// 	cmd->redirs = NULL; // Use the single redirections list
// 	cmd->next = NULL;
// 	return (cmd);
// }

// // Helper to append a redirection to a list.
// // Also from your friend's 'test.c'
// void append_redir(t_redirs **list, t_redirs *new_redir)
// {
// 	t_redirs	*tmp;

// 	if (!*list)
// 		*list = new_redir;
// 	else
// 	{
// 		tmp = *list;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_redir;
// 	}
// }


// THE NEW, CORRECT PARSING LOGIC
t_cmd	*parse_tokens_to_commands(t_ptr **head, t_tkn *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*curr_cmd;
	t_tkn	*current_token;

	if (!tokens)
		return (NULL);
	cmd_list = init_new_cmd(head);
	curr_cmd = cmd_list;
	current_token = tokens;
	while (current_token)
	{
		if (current_token->tkn_typ == PI)
		{
			curr_cmd->next = init_new_cmd(head);
			curr_cmd = curr_cmd->next;
		}
		else if (current_token->tkn_typ >= red_in && current_token->tkn_typ <= HEREDOC)
		{
			t_redirs *redir = ft_mall(head, sizeof(t_redirs));
			redir->type = current_token->tkn_typ;
			if (current_token->next && current_token->next->tkn_typ == wrd)
			{
				redir->filename = ft_strdup1(head, current_token->next->vl);
				current_token = current_token->next; // Skip the filename token
			}
			else
			{
				// Handle syntax error: redirection with no file
				redir->filename = ft_strdup1(head, "");
			}
			redir->next = NULL;
			append_redir(&(curr_cmd->redirs), redir);
		}
		else if (current_token->tkn_typ == wrd)
		{
			append_arg(head, &(curr_cmd->args), current_token->vl);
		}
		current_token = current_token->next;
	}
	return (cmd_list);
}
