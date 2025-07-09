/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:12:43 by mteffahi          #+#    #+#             */
/*   Updated: 2025/06/13 17:22:33 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	else
		return (0);
}

int	chek_equal(char *vl)
{
	int	i;

	i = -1;
	while (vl[++i])
	{
		if (vl[i] == '=')
			return (1);
	}
	return (0);
}

void	set_node(t_env **head, t_ptr **ptr_head, char *env_val)
{
	t_env	*node;

	node = ft_mall(ptr_head, sizeof(t_env));
	node->var = ft_strdup(ptr_head, env_val);
	if (!node->var)
	{
		ft_mall(ptr_head, 0);
		return ;
	}
	node->next = NULL;
	ft_lstadd_back_env(head, node);
}

t_env	*set_env_ls(t_ptr **head_ptr, char **env)
{
	t_env	*set;
	int		i;

	if (!env || !*env)  // Check both env and *env
		return (NULL);
	set = NULL;
	i = 0;
	while (env[i])
	{
		set_node(&set, head_ptr, env[i]);
		i++;
	}
	return (set);
}

// static	char	*get_vl(t_ptr **head, char *env)
// {
// 	int		i;
// 	char	*str;
// 	int		j;

// 	i = 0;
// 	while (env[i] && env[i] != '\"')
// 	{
// 		i++;
// 	}
// 	str = ft_mall(head, (i + 1));
// 	j = 0;
// 	while (j < i)
// 	{
// 		str[j] = env[i];
// 		j++;
// 	}
// 	str[j] = '\0';
// 	return (str);
// }

// static char *gt_nm_helper(t_ptr **ptr_head, char *env_str, char *name)
// {
// 	int	i;

// 	i = 0;
// 	while (env_str[i])
// 	{
// 		if (env_str[i] == '\"')
// 		{
// 			i++;
// 			break ;
// 		}
// 		i++;
// 	}
// }

// int ft_strcmp_vr(char *s1, char *s2, size_t size)
// {
// 	size_t i = 0;

// 	(void)size;
// 	while (s1[i] && s1[i] != '=')
// 	{
// 		i++;
// 	}
// 	i++;
// 	while (s1[i] && s2[i])
// 	{
// 		if (s1[i] != s2[i])
// 			return (s1[i] - s2[i]);
// 		i++;
// 	}
// 	return (s1[i] - s2[i]);
// }

// Compare environment variable name (before '=') with given name
// int ft_strcmp_vr(char *env_var, char *name, size_t name_len)
// {
// 	size_t i = 0;

// 	// Check for NULL pointers
// 	if (!env_var || !name)
// 		return (-1);
	
// 	// Compare character by character up to name_len or until we hit '='
// 	while (i < name_len && env_var[i] && env_var[i] != '=' && name[i])
// 	{
// 		if (env_var[i] != name[i])
// 			return (env_var[i] - name[i]);
// 		i++;
// 	}
	
// 	// Check if we've matched the entire name and the next char in env_var is '='
// 	if (i == name_len && env_var[i] == '=' && name[i] == '\0')
// 		return (0);  // Perfect match
	
// 	// Handle edge cases
// 	if (env_var[i] == '=' && name[i] == '\0')
// 		return (0);  // Match found
// 	if (env_var[i] == '\0' && name[i] == '\0')
// 		return (0);  // Both strings ended, match
	
// 	// Default case - strings don't match
// 	return (env_var[i] - name[i]);
// }

// Alternative simpler version if you prefer:
int ft_strcmp_vr(char *env_var, char *name, size_t name_len)
{
	size_t i = 0;

	if (!env_var || !name)
		return (-1);
	
	// Compare only the name part (before '=')
	while (i < name_len && env_var[i] && name[i] && env_var[i] != '=')
	{
		if (env_var[i] != name[i])
			return (env_var[i] - name[i]);
		i++;
	}
	
	// Check if we matched the full name and found '=' or end of env_var
	if (i == name_len && (env_var[i] == '=' || env_var[i] == '\0') && name[i] == '\0')
		return (0);
	
	return (1); // No match
}

char	*extract_vl(t_ptr **ptr_head, char *variable)
{
	int		i;
	char	*value;
	int		len;

	i = 0;
	if (!variable)
		printf("NULL\n");
	if (!variable)  // Return early if variable is NULL
		return (NULL);
	// Skip to the first quote or '=' sign (assuming format VAR="value" or VAR=value)
	while (variable[i] && variable[i] != '=' && variable[i] != '"')
		i++;
	
	// If we found '=', move past it
	if (variable[i] == '=')
		i++;
	if (variable[i] == '"')
		i++;
	len = i;
	while (variable[len] && variable[len] != '"')
		len++;
	value = ft_mall(ptr_head, ((len  - i )+ 1));
	int j = 0;
	while (i < len && variable[i])
	{
		value[j] = variable[i];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

char	*get_vr(t_env **head, t_ptr **head_ptr, char *name)
{
	t_env	*tmp;
	char	*str;
	size_t	size;

	if (!head || !*head || !name)  // Add null checks
		return (NULL);
	tmp = *head;
	size = ft_strlen(name);
	while (tmp)
	{
		if (tmp->var && !(ft_strcmp_vr(tmp->var, name, size)))
		{
			str = ft_strdup(head_ptr, tmp->var);
			return (str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

// void	handl_var_name(t_ptr **head, t_tkn **tkns)
// {
// 	t_tkn	*tmp;

// 	tmp = *tkns;
// 	while (tmp)
// 	{
// 		if (chek_equal(tmp->vl))
// 	}
	
// }
