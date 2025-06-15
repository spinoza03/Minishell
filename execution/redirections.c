/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:48:07 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/14 19:54:34 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

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