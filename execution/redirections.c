/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:48:07 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/17 16:40:43 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int handle_redir_out(const char *filename)
{
    int fd;

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
        else if (current->type == red_apnd)
        {
            if (handle_redir_append(current->filename) != 0)
                return (1);
        }
        else if (current->type == red_in) // Add this else if block
        {
            if (handle_redir_in(current->filename) != 0)
                return (1);
        }
        current = current->next;
    }
    return (0);
}

int apply_redirections(t_cmd *command, int original_fds[2])
{
    // First, save the original standard input and output file descriptors.
    original_fds[0] = dup(STDIN_FILENO);
    original_fds[1] = dup(STDOUT_FILENO);
    if (original_fds[0] == -1 || original_fds[1] == -1)
    {
        perror("minishell: dup");
        return (1);
    }
    if (!command)
        return (0);
    if (process_redir_list(command->pre_redirs) != 0)
        return (1); // An error occurred in one of the redirections
    if (process_redir_list(command->post_redirs) != 0)
        return (1); // An error occurred in one of the redirections
        
    return (0); // All redirections were applied successfully
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