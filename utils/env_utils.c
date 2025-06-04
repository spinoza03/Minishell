/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:43:48 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/04 13:53:10 by ilallali         ###   ########.fr       */
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
char *resolve_command_path_part1(const char *command_name, t_env_copy *env_list)
{
    char *path_env_value;
    char **directories;
    int i;

    if (!command_name)
        return (NULL);

    // 1. If command_name contains a '/', it's an absolute or relative path.
    //    (We'll handle access check for this later, for now just acknowledge it)
    //    For this part, if it contains '/', we won't do PATH search.
    //    Real implementation would check access(command_name, X_OK)
    //    and return strdup(command_name) if OK.
    if (strchr(command_name, '/') != NULL) // Using strchr, or your ft_strchr
    {
        printf("DEBUG (resolve_command_path): '%s' is a path, skipping PATH search for now.\n", command_name);
        // For a real implementation here:
        // if (access(command_name, X_OK) == 0)
        //     return (strdup(command_name)); // Or ft_strdup
        // else
        //     return (NULL); // Path given but not accessible/executable
        return (NULL); // Placeholder for now
    }

    // 2. Get the PATH environment variable value.
    path_env_value = get_env_value(env_list, "PATH");
    if (!path_env_value)
    {
        printf("DEBUG (resolve_command_path): PATH variable not found.\n");
        return (NULL);
    }
    printf("DEBUG (resolve_command_path): PATH = \"%s\"\n", path_env_value);

    // 3. Split the PATH value by ':'
    //    Ensure your ft_split handles NULL or empty strings gracefully if path_env_value could be so.
    directories = ft_split(path_env_value, ':'); // Assuming ft_split is from your Libft
    if (!directories)
    {
        perror("minishell: ft_split error in resolve_command_path");
        return (NULL); // ft_split failed (e.g., malloc error)
    }

    // 4. For now, just print the directories (DEBUG)
    i = 0;
    while (directories[i])
    {
        printf("DEBUG (resolve_command_path): PATH dir[%d] = \"%s\"\n", i, directories[i]);
        i++;
    }

    // 5. Free the allocated memory for 'directories'
    //    (You'll need a helper function in Libft to free a char** (array of strings))
    //    Let's call it ft_free_str_array or similar.
    //    For now, manual free for this debug version:
    i = 0;
    while (directories[i])
    {
        free(directories[i]);
        directories[i] = NULL;
        i++;
    }
    free(directories);
    directories = NULL;

    // We will build and return the actual path in the next step.
    return (NULL); // Placeholder for now, as we are not yet returning a resolved path.
}
