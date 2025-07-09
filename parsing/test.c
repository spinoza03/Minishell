/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:58:39 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/07 14:47:54 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *init_new_cmd(t_ptr **head)
{
    t_cmd *cmd = ft_mall(head, sizeof(t_cmd));
    cmd->args = NULL;
    cmd->pre_redirs = NULL;
    cmd->post_redirs = NULL;
    cmd->next = NULL;
    return cmd;
}

void append_redir(t_redirs **list, t_redirs *new_redir)
{
    if (!*list)
        *list = new_redir;
    else {
        t_redirs *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_redir;
    }
}

void append_arg(t_ptr **head, char ***args, char *word)
{
    int count = 0;
	int i = 0;

    if (*args) {
        while ((*args)[count])
            count++;
    }

    char **new_args = ft_mall(head, (sizeof(char *) * (count + 2)));

    while (i < count)
	{
        new_args[i] = (*args)[i];
		i++;
	}

    new_args[count] = ft_strdup(head, word);
    new_args[count + 1] = NULL;
    *args = new_args;
}
