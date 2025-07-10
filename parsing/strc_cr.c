/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strc_cr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:14:48 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/10 00:12:39 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

t_cmd	*init_new_cmd(t_ptr **head)
{
	t_cmd	*cmd;

	cmd = ft_mall(head, sizeof(t_cmd));
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	append_redir(t_redirs **list, t_redirs *new_redir)
{
	t_redirs	*tmp;

	if (!*list)
		*list = new_redir;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

void	append_arg(t_ptr **head, char ***args, char *word)
{
	int		count;
	char	**new_args;
	int		i;

	count = 0;
	if (*args)
		while ((*args)[count])
			count++;
	new_args = ft_mall(head, (sizeof(char *) * (count + 2)));
	i = 0;
	while (i < count)
	{
		new_args[i] = (*args)[i];
		i++;
	}
	new_args[count] = ft_strdup1(head, word);
	new_args[count + 1] = NULL;
	*args = new_args;
}

// CORRECTED LOGIC
t_cmd	*parse_tokens_to_commands(t_ptr **head, t_tkn *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*curr_cmd;
	t_tkn	*current_token;

	cmd_list = NULL;
	curr_cmd = NULL;
	current_token = tokens;
	while (current_token)
	{
		// If there is no current command, create one.
		if (curr_cmd == NULL)
		{
			curr_cmd = init_new_cmd(head);
			if (cmd_list == NULL)
				cmd_list = curr_cmd;
		}
		if (current_token->tkn_typ == PI)
		{
			// Create a new command for the next part of the pipe.
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
				current_token = current_token->next;
			}
			else
				redir->filename = ft_strdup1(head, "");
			redir->next = NULL;
			append_redir(&(curr_cmd->redirs), redir);
		}
		else if (current_token->tkn_typ == wrd)
			append_arg(head, &(curr_cmd->args), current_token->vl);
		current_token = current_token->next;
	}
	return (cmd_list);
}
