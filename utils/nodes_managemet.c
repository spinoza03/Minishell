/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_managemet.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:09:01 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/03 16:16:23 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	ft_lstadd_back(t_env_copy **lst, t_env_copy *new_node)
{
	if (!lst || !new_node)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new_node;
	else
		*lst = new_node;
}

void	ft_lstadd_front(t_env_copy **lst, t_env_copy *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new ;
}

t_env_copy	*ft_lstlast(t_env_copy *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next != NULL)
	{
		lst = lst -> next;
	}
	return (lst);
}

void env_lstclear(t_env_copy **list_head)
{
    t_env_copy *current;
    t_env_copy *next_node;

    if (!list_head || !*list_head)
        return;
    current = *list_head;
    while (current) {
        next_node = current->next;
        del_env_node_content(current);
        free(current);
        current = next_node;
    }
    *list_head = NULL;
}

t_env_copy *env_lstnew(char *key_str, char *value_str)
{
    t_env_copy *new_node;

    new_node = (t_env_copy *)malloc(sizeof(t_env_copy));
    if (!new_node) {
        perror("minishell: malloc for env_lstnew");
        return (NULL);
    }
    new_node->key = ft_strdup(key_str);
    new_node->value = ft_strdup(value_str);
    if (!new_node->key || !new_node->value) {
        perror("minishell: ft_strdup in env_lstnew");
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return (NULL);
    }
    new_node->next = NULL;
    return (new_node);
}
