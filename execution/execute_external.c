/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allali <allali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:58:23 by allali            #+#    #+#             */
/*   Updated: 2025/06/01 23:58:48 by allali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int execute_external_command(t_cmd *command, char **original_envp)
{
    pid_t   pid;
    int     exit_status;

    // Default exit status in case of fork failure before child/parent logic.
    exit_status = 1;

    pid = fork(); // fork() is an allowed function

    if (pid == -1)
    {
        // Fork failed
        perror("minishell: fork"); // perror() is an allowed function
        return (1); // Return an error status
    }

    if (pid == 0)
    {
        // --- Child Process ---
        // child_process_execution will call execve and exit.
        // It does not return if execve is successful.
        child_process_execution(command, original_envp);
        // The line below should ideally not be reached if child_process_execution
        // handles all exit paths (e.g., exit() after failed execve).
        // Adding it for robustness in case child_process_execution had an oversight.
        exit(127); // Fallback exit for child if execve logic somehow bypasses exit
    }
    else
    {
        // --- Parent Process ---
        // Wait for the child and get its exit status.
        exit_status = parent_process_wait(pid);
    }
    return (exit_status);
}