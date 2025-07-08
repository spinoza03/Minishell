/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:43:48 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/08 15:36:27 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char *get_env_value(t_env_copy *env_list, const char *key)
{
    t_env_copy *current;

    if (!env_list || !key)
        return (NULL);
    current = env_list;
    while (current != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            return (current->value);
        }
        current = current->next;
    }
    return (NULL);
}
static char	*check_absolute_path(const char *command_name)
{
	if (ft_strchr(command_name, '/'))
	{
		if (access(command_name, X_OK) == 0)
			return (ft_strdup(command_name));
		else
			return (NULL);
	}
	return (NULL);
}

// Helper 2: Searches for the command in the directories from the PATH variable.
static char	*search_in_path(const char *cmd, char **dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		// Note: A real implementation would use ft_strjoin for safety.
		// This is kept simple to match your existing style.
		full_path = malloc(ft_strlen(dirs[i]) + ft_strlen(cmd) + 2);
		if (!full_path)
			return (NULL);
		ft_strcpy(full_path, dirs[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

// The main function, now clean and under 25 lines.
char	*resolve_command_path(const char *command_name, t_env_copy *env_list)
{
	char	*path_env;
	char	**directories;
	char	*executable_path;

	if (!command_name || !*command_name)
		return (NULL);
	executable_path = check_absolute_path(command_name);
	if (executable_path)
		return (executable_path);
	path_env = get_env_value(env_list, "PATH");
	if (!path_env || !*path_env)
		return (NULL);
	directories = ft_split(path_env, ':');
	if (!directories)
		return (NULL);
	executable_path = search_in_path(command_name, directories);
	ft_free_str_array(directories);
	return (executable_path);
}

int set_env_value(t_env_copy **env_list, const char *key, const char *new_value)
{
    t_env_copy *current;

    current = *env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            if (new_value)
                current->value = ft_strdup(new_value);
            else
                current->value = NULL;
            return (0);
        }
        current = current->next;
    }
    t_env_copy *new_node = env_lstnew((char *)key, (char *)new_value);
    if (!new_node)
        return (1);
    ft_lstadd_back(env_list, new_node);
    return (0);
}
