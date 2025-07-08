/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:47:09 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/08 13:34:35 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int handle_redir_in(const char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror(filename);
        return (1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("minishell: dup2");
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}
char *handle_heredoc_read(const char *delimiter)
{
    char    *line;
    char    *temp_filename;
    int     fd;

    temp_filename = ft_strdup("/tmp/minishell_heredoc");
    if (!temp_filename)
        return (NULL);
    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
    {
        perror("minishell: heredoc");
        free(temp_filename);
        return (NULL);
    }
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
    return (temp_filename);
}
