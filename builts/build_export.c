/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:15:19 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/16 22:27:00 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"


static int	pars_export_arg(char *arg, char **key, char **value)
{
	char	*equal_sign_pos;

	equal_sign_pos = ft_strchr(arg, '=');
	if (equal_sign_pos == NULL)
	{
		*key = ft_strdup(arg);
		*value = NULL;
		if (!*key)
			return (1);
		return (0);
	}
	*value = ft_strdup(equal_sign_pos + 1);
	if (!*value)
		return (1);
	*equal_sign_pos = '\0';
	*key = ft_strdup(arg);
	*equal_sign_pos = '=';
	if (!*key)
	{
		free(*value);
		*value = NULL;
		return (1);
	}
	return (0);
}

static int	print_export_format(t_shell *shell)
{
	t_env_copy	*current;

	current = *(shell->env_list);
	while (current)
	{
		write(1, "declare -x ", 11);
		write(1, current->key, ft_strlen(current->key));
		if (current->value != NULL)
		{
			write(1, "=\"", 2);
			write(1, current->value, ft_strlen(current->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		current = current->next;
	}
	return (0);
}
static int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
// NEW, SMARTER LOGIC HERE
// int	exec_export(t_cmd *command, t_shell *shell)
// {
// 	int		i;
// 	char	*key;
// 	char	*value;
// 	char	*full_arg;

// 	i = 1;
// 	if (!command->args[i])
// 		return (print_export_format(shell));
// 	while (command->args[i])
// 	{
// 		if (command->args[i][ft_strlen(command->args[i]) - 1] == '='
// 			&& command->args[i + 1])
// 		{
// 			full_arg = ft_strjoin(command->args[i], command->args[i + 1]);
// 			i++;
// 		}
// 		else
// 			full_arg = ft_strdup(command->args[i]);
// 		if (pars_export_arg(full_arg, &key, &value) == 0)
// 		{
// 			if (!is_valid_identifier(key))
// 			{
// 				write(2, "minishell: export: `", 20);
// 				write(2, full_arg, ft_strlen(full_arg));
// 				write(2, "': not a valid identifier\n", 26);
// 			}
// 		}
// 		else
// 			set_env_value(shell->env_list, key, value);
// 		free(full_arg);
// 		free(key);
// 		free(value);
// 		i++;
// 	}
// 	return (0);
// }

int	exec_export(t_cmd *command, t_shell *shell)
{
	int		i;
	char	*key;
	char	*value;
	char	*full_arg;

	i = 1;
	if (!command->args[i])
		return (print_export_format(shell));
	while (command->args[i])
	{
		if (command->args[i][ft_strlen(command->args[i]) - 1] == '='
			&& command->args[i + 1])
		{
			full_arg = ft_strjoin(command->args[i], command->args[i + 1]);
			i++;
		}
		else
			full_arg = ft_strdup(command->args[i]);
		
		if (pars_export_arg(full_arg, &key, &value) == 0)  // SUCCESS case
		{
			if (!is_valid_identifier(key))
			{
				write(2, "minishell: export: `", 20);
				write(2, full_arg, ft_strlen(full_arg));
				write(2, "': not a valid identifier\n", 26);
			}
			else
			{
				// Actually set the variable when parsing succeeds AND identifier is valid
				set_env_value(shell->env_list, key, value);
			}
		}
		else
		{
			// If parsing failed, key and value might not be properly allocated
			// Don't try to free them or use them
			free(full_arg);
			i++;
			continue;
		}
		// If parsing fails, we don't set anything (which is correct behavior)
		
		free(full_arg);
		free(key);
		free(value);
		i++;
	}
	return (0);
}
