/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:44:32 by ilallali          #+#    #+#             */
/*   Updated: 2025/05/31 18:08:39 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void create_env_list(t_env_copy **list_head, char **env)
{
	int			i;
	char		*key;
	char		*value;
	t_env_copy	*new_node;

	*list_head = NULL;
	i = 0;
	while (env[i])
	{
		key = NULL;
		value = NULL;
		if(parse_env(env[i], &key, &value))
		{
			new_node = env_lstnew(key, value);
			free(key);
			free(value);
			if(!new_node)
			{
				env_lstclear(list_head);
				exit(EXIT_FAILURE);
			}
			ft_lstadd_back(list_head, new_node);
		}		
	}
}
