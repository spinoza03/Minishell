/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strc_cr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:14:48 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/07 14:48:51 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*crt_cmd(t_ptr **ptr)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = ft_mall(ptr, sizeof(t_cmd));
	cmd->args = NULL;
	cmd->post_redirs = NULL;
	cmd->pre_redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parse_tokens_to_commands(t_ptr **head, t_tkn *tokens)
{
   t_cmd *cmd_list;
    t_cmd *curr_cmd; 

    int redir_state;

	cmd_list = NULL;
	curr_cmd = NULL;
	redir_state = 0;
    while (tokens) {
        if (tokens->tkn_typ == wrd) {
            if (redir_state != 0) {
                t_redirs *redir = ft_mall(head, sizeof(t_redirs));
                redir->filename = ft_strdup(head, tokens->vl); 
                if (redir_state == 1)
                    redir->type = red_in;
                else if (redir_state == 2)
                    redir->type = red_out;
                else if (redir_state == 3)
                    redir->type = red_apnd;
                else if (redir_state == 4)
                    redir->type = HEREDOC;

                redir->next = NULL;
                if (redir_state == 1 || redir_state == 4)
                    append_redir(&(curr_cmd->pre_redirs), redir);
                else
                    append_redir(&(curr_cmd->post_redirs), redir);

                redir_state = 0;
            } else {
                if (!curr_cmd) {
                    curr_cmd = init_new_cmd(head);
                    cmd_list = curr_cmd;
                }
                append_arg(head, &(curr_cmd->args), tokens->vl);
            }
        }
		else if (tokens->tkn_typ == red_in)
            redir_state = 1;
        else if (tokens->tkn_typ == red_out)
            redir_state = 2;
        else if (tokens->tkn_typ == red_apnd)
            redir_state = 3;
        else if (tokens->tkn_typ == HEREDOC)
            redir_state = 4;
        else if (tokens->tkn_typ == PI) {
            t_cmd *new_cmd = init_new_cmd(head);

            if (!cmd_list)
                cmd_list = new_cmd;
            else
                curr_cmd->next = new_cmd;

            curr_cmd = new_cmd;
        }

        tokens = tokens->next;
    }

    return cmd_list;
}