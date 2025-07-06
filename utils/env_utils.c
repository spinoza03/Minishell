/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:43:48 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/06 16:03:55 by ilallali         ###   ########.fr       */
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
char *resolve_command_path(const char *command_name, t_env_copy *env_list)
{
    char *path_env_value;
    char **directories;
    char *full_path;
    int i;

    if (!command_name || *command_name == '\0')
        return (NULL);
    if (strchr(command_name, '/') != NULL)
    {
        if (access(command_name, X_OK) == 0)
            return (ft_strdup(command_name));
        else
            return (NULL);
    }
    path_env_value = get_env_value(env_list, "PATH");
    if (!path_env_value || *path_env_value == '\0') 
        return (NULL);
    directories = ft_split(path_env_value, ':'); 
    if (!directories)
		return (NULL);
    i = 0;
    full_path = NULL;
    while (directories[i])
    {
        size_t dir_len = ft_strlen(directories[i]);
        size_t cmd_len = ft_strlen(command_name);
        full_path = (char *)malloc(dir_len + 1 + cmd_len + 1);
        if (!full_path)
        {
            ft_free_str_array(directories);
            return (NULL);
        }
        ft_strcpy(full_path, directories[i]);
        ft_strcat(full_path, "/");
        ft_strcat(full_path, command_name);
        if (access(full_path, X_OK) == 0)
        {
            ft_free_str_array(directories);
            return (full_path);
        }
        free(full_path);
        full_path = NULL;
        i++;
    }
    ft_free_str_array(directories);
    return (NULL);
}

int set_env_value(t_env_copy **env_list, const char *key, const char *new_value)
{
    t_env_copy *current;

    current = *env_list;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value); // Free the old value string
            if (new_value) // If the new value is not NULL...
                current->value = ft_strdup(new_value);
            else // ...otherwise, set the pointer to NULL.
                current->value = NULL;
            // TODO: check strdup failure
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
