/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:18:56 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/10 18:16:35 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num_str;
	char		*filename;

	num_str = ft_itoa(i++);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/tmp/heredoc_", num_str);
	free(num_str);
	return (filename);
}

void	handle_heredoc_read_child(const char *delimiter,
		const char *temp_filename)
{
	char	*line;
	int		fd;

	signal(SIGINT, SIG_DFL);
	fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	exit(0);
}

static int	fork_and_wait_heredoc(t_redirs *redir, const char *temp_filename)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		handle_heredoc_read_child(redir->filename, temp_filename);
	waitpid(pid, &status, 0);
	signal(SIGINT, sigint_handler);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (1);
	return (0);
}

int	execute_single_heredoc(t_redirs *redir)
{
	char	*temp_filename;

	temp_filename = generate_heredoc_filename();
	if (!temp_filename)
		return (1);
	if (fork_and_wait_heredoc(redir, temp_filename) != 0)
	{
		free(temp_filename);
		return (1);
	}
	redir->filename = temp_filename;
	redir->type = red_in;
	return (0);
}

int	process_heredocs(t_cmd *cmd_list)
{
	t_cmd		*current_cmd;
	t_redirs	*redir;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		redir = current_cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (execute_single_heredoc(redir) != 0)
					return (1);
			}
			redir = redir->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}
