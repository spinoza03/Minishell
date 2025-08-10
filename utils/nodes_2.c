/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:40:32 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/10 18:19:18 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	del_env_node_content(t_env_copy *node)
{
	if (!node)
		return ;
	if (node->key)
	{
		free(node->key);
		node->key = NULL;
	}
	if (node->value)
	{
		free(node->value);
		node->value = NULL;
	}
}

void	env_lstdel_one(t_env_copy **list_head, const char *key)
{
	t_env_copy	*current;
	t_env_copy	*prev;

	if (!list_head || !*list_head || !key)
		return ;
	current = *list_head;
	prev = NULL;
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	if (prev == NULL)
		*list_head = current->next;
	else
		prev->next = current->next;
	del_env_node_content(current);
	free(current);
}
