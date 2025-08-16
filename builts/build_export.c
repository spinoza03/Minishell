/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allali <allali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:15:19 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/16 20:06:21 by allali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return (1);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_assign(char *arg, char **key, char **value)
{
	char	*op_pos;
	int		op_type;

	op_type = 1;
	op_pos = ft_strchr(arg, '+');
	if (op_pos && op_pos[1] == '=')
		op_type = 2;
	else
		op_pos = ft_strchr(arg, '=');
	if (op_pos == NULL)
	{
		*key = ft_strdup(arg);
		*value = NULL;
		return (0);
	}
	*value = ft_strdup(op_pos + op_type);
	*op_pos = '\0';
	*key = ft_strdup(arg);
	if (op_type == 2)
		op_pos[0] = '+';
	else
		op_pos[0] = '=';
	return (op_type);
}

static void	append_to_env(t_shell *shell, char *key, char *value)
{
	char	*old_value;
	char	*new_value;

	old_value = get_env_value(*(shell->env_list), key);
	if (old_value)
	{
		new_value = ft_strjoin(old_value, value);
		set_env_value(shell->env_list, key, new_value);
		free(new_value);
	}
	else
		set_env_value(shell->env_list, key, value);
}

static void	process_export_arg(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	int		assign_type;

	assign_type = parse_assign(arg, &key, &value);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
	{
		if (assign_type == 2)
			append_to_env(shell, key, value);
		else
			set_env_value(shell->env_list, key, value);
	}
	free(key);
	if (value)
		free(value);
}

int	exec_export(t_cmd *command, t_shell *shell)
{
	int		i;
	char	*full_arg;
	char	*current_arg;

	i = 1;
	if (!command->args[i])
		return (print_export_format(shell));
	while (command->args[i])
	{
		current_arg = command->args[i];
		if (current_arg[ft_strlen(current_arg) - 1] == '='
			&& command->args[i + 1])
		{
			full_arg = ft_strjoin(current_arg, command->args[i + 1]);
			if (!full_arg)
				return (1); // Malloc error
			process_export_arg(full_arg, shell);
			free(full_arg);
			i += 2; // We consumed two arguments, so skip ahead
		}
		else
		{
			process_export_arg(current_arg, shell);
			i += 1; // We consumed one argument
		}
	}
	return (0);
}
