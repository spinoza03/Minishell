/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:44:32 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/08 15:36:01 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	parse_no_equal(const char *env_s, char **key, char **val)
{
	*key = ft_strdup(env_s);
	if (!(*key))
	{
		perror("minishell: malloc");
		return (0);
	}
	*val = ft_strdup("");
	if (!(*val))
	{
		perror("minishell: malloc");
		free(*key);
		*key = NULL;
		return (0);
	}
	return (1);
}

// Helper 2: Handles parsing when the string has an '='.
static int	parse_with_equal(const char *env_s, char *eq_pos,
							char **key, char **val)
{
	size_t	key_len;

	key_len = eq_pos - env_s;
	*key = malloc(key_len + 1);
	if (!(*key))
	{
		perror("minishell: malloc");
		return (0);
	}
	ft_memcpy(*key, env_s, key_len);
	(*key)[key_len] = '\0';
	*val = ft_strdup(eq_pos + 1);
	if (!(*val))
	{
		perror("minishell: malloc");
		free(*key);
		*key = NULL;
		return (0);
	}
	return (1);
}

// The main function, now clean and under the line limit.
int	parse_env(const char *env_string, char **key_ptr, char **value_ptr)
{
	char	*equal_sign_pos;

	*key_ptr = NULL;
	*value_ptr = NULL;
	if (!env_string || !key_ptr || !value_ptr)
		return (0);
	equal_sign_pos = ft_strchr(env_string, '=');
	if (equal_sign_pos == NULL)
	{
		if (parse_no_equal(env_string, key_ptr, value_ptr) == 0)
			return (0);
	}
	else
	{
		if (parse_with_equal(env_string, equal_sign_pos,
				key_ptr, value_ptr) == 0)
			return (0);
	}
	return (1);
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
