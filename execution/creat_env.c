/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allali <allali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:44:32 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/27 17:04:03 by allali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int parse_env(const char *env_string, char **key_ptr, char **value_ptr)
{
    char    *equal_sign_pos;
    size_t  key_len;

    *key_ptr = NULL;
    *value_ptr = NULL;
    if (!env_string || !key_ptr || !value_ptr)
        return (0); 

    equal_sign_pos = strchr(env_string, '=');

    if (equal_sign_pos == NULL) // Case: No '='
    {
        key_len = strlen(env_string);
        *key_ptr = (char *)malloc(key_len + 1);
        if (!(*key_ptr))
        {
            perror("minishell: malloc for key (no '=')");
            return (0);
        }
        strcpy(*key_ptr, env_string);
        *value_ptr = ft_strdup("");
        if (!(*value_ptr))
        {
            perror("minishell: malloc for empty value (no '=')");
            free(*key_ptr);
            *key_ptr = NULL;
            return (0);
        }
        return (1);
    }
    else // Case: '=' was found
    {
        key_len = equal_sign_pos - env_string; 
        *key_ptr = (char *)malloc(key_len + 1);
        if (!(*key_ptr))
        {
            perror("minishell: malloc for key");
            return (0);
        }
        strncpy(*key_ptr, env_string, key_len);
        (*key_ptr)[key_len] = '\0';

        *value_ptr = (char *)malloc(strlen(equal_sign_pos + 1) + 1);
        if (!(*value_ptr))
        {
            perror("minishell: malloc for value");
            free(*key_ptr);
            *key_ptr = NULL;
            return (0);
        }
        strcpy(*value_ptr, equal_sign_pos + 1);
        return (1);
    }
}

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
		i++;
	}
}
