/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:18:56 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/10 15:01:02 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void handle_heredoc_read_child(const char *delimiter, const char *temp_filename)
{
    char    *line;
    int     fd;

    signal(SIGINT, SIG_DFL); // Reset Ctrl-C to default for the child
    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
        exit(1);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    exit(0);
}

int	execute_single_heredoc(t_redirs *redir)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		handle_heredoc_read_child(redir->filename, "/tmp/heredoc_tmp");
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (1);
	redir->filename = ft_strdup("/tmp/heredoc_tmp");
	if (!redir->filename)
		return (1);
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
			if (redir->type == red_in && ft_strcmp(redir->filename, "/tmp/heredoc_tmp") == 0)
			{
				free(redir->filename);
				redir->filename = NULL; 
			}
			redir = redir->next;
		}
		current_cmd = current_cmd->next;
	}
}
