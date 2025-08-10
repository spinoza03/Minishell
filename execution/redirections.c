/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:48:07 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/10 19:30:10 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	handle_redir_out(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_append(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	process_redir_list(t_redirs *list)
{
	t_redirs	*current;
	int			error_status;

	current = list;
	error_status = 0;
	while (current)
	{
		if (current->type == red_out)
		{
			if (handle_redir_out(current->filename) != 0)
				error_status = 1;
		}
		else if (current->type == red_apnd)
		{
			if (handle_redir_append(current->filename) != 0)
				error_status = 1;
		}
		else if (current->type == red_in)
		{
			if (handle_redir_in(current->filename) != 0)
				error_status = 1;
		}
		current = current->next;
	}
	return (error_status);
}

int	apply_redirections(t_cmd *command, int original_fds[2])
{
	original_fds[0] = dup(STDIN_FILENO);
	original_fds[1] = dup(STDOUT_FILENO);
	if (original_fds[0] == -1 || original_fds[1] == -1)
	{
		perror("minishell: dup");
		return (1);
	}
	if (!command)
		return (0);
	if (process_redir_list(command->redirs) != 0)
		return (1);
	return (0);
}

void	restore_redirections(int original_fds[2])
{
	if (dup2(original_fds[0], STDIN_FILENO) == -1)
		perror("minishell: dup2 restore stdin");
	if (dup2(original_fds[1], STDOUT_FILENO) == -1)
		perror("minishell: dup2 restore stdout");
	close(original_fds[0]);
	close(original_fds[1]);
}
