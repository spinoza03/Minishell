/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:48:07 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/16 22:06:44 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int handle_redir_append(const char *filename)
{
    int fd;

    // O_APPEND: The key difference. It makes all writes go to the end of the file.
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

static int process_redir_list(t_redirs *list)
{
    t_redirs *current;

    current = list;
    while (current)
    {
        if (current->type == red_out)
        {
            if (handle_redir_out(current->filename) != 0)
                return (1);
        }
        else if (current->type == red_apnd) // Add this else if block
        {
            if (handle_redir_append(current->filename) != 0)
                return (1);
        }
        // else if (current->type == red_in)   { /* TODO: handle < */ }

        current = current->next;
    }
    return (0); // Success
}

int apply_redirections(t_cmd *command, int original_fds[2])
{

    original_fds[0] = dup(STDIN_FILENO);
    original_fds[1] = dup(STDOUT_FILENO);
    if (original_fds[0] == -1 || original_fds[1] == -1)
    {
        perror("minishell: dup");
        return (1);
    }

    (void)command;
    return (0);
}

void restore_redirections(int original_fds[2])
{
    if (dup2(original_fds[0], STDIN_FILENO) == -1)
        perror("minishell: dup2 restore stdin");
    if (dup2(original_fds[1], STDOUT_FILENO) == -1)
        perror("minishell: dup2 restore stdout");
    close(original_fds[0]);
    close(original_fds[1]);
}