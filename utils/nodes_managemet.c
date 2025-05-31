/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_managemet.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:09:01 by ilallali          #+#    #+#             */
/*   Updated: 2025/05/31 17:16:13 by ilallali         ###   ########.fr       */
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

int	ft_lstsize(t_env_copy *lst)
{
	int		count;
	t_env_copy	*node;

	node = lst;
	count = 0;
	while (node != NULL)
	{
		count++;
		node = node->next;
	}
	return (count);
}
