/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:16:34 by allali            #+#    #+#             */
/*   Updated: 2025/08/10 18:16:53 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	convert_to_str(char *str, unsigned int n, int *length)
{
	while (n > 0)
	{
		str[--(*length)] = (n % 10) + '0';
		n /= 10;
	}
}

static int	get_num_length(int n)
{
	int	length;

	if (n <= 0)
		length = 1;
	else
		length = 0;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				length;
	unsigned int	num;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = get_num_length(n);
	str = (char *)malloc(length + 1);
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (n == 0)
		str[0] = '0';
	else
		convert_to_str(str, num, &length);
	return (str);
}

int	print_export_format(t_shell *shell)
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

void	cleanup_heredocs(t_cmd *cmd_list)
{
	t_cmd		*current_cmd;
	t_redirs	*redir;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		redir = current_cmd->redirs;
		while (redir)
		{
			if (redir->type == red_in
				&& ft_strncmp(redir->filename, "/tmp/heredoc_", 13) == 0)
			{
				unlink(redir->filename);
				free(redir->filename);
				redir->filename = NULL;
			}
			redir = redir->next;
		}
		current_cmd = current_cmd->next;
	}
}
