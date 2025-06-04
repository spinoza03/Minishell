/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:47:38 by allali            #+#    #+#             */
/*   Updated: 2025/06/04 18:14:29 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	child_process_execution(const char *exec_path, char **args, char **original_envp)
{
    // Important: Later, you will handle file redirections (dup2) here,
    // just before calling execve.

    if (execve(exec_path, args, original_envp))
    {
        // If execve fails, print an error and exit the child.
        // perror(command->args[0]); // Good to include the command name in the error
        exit(127); // Standard exit code for "command not found" or exec error
    }
    // If execve is successful, this part of the code is replaced by the new program,
    // so the child process does not continue executing code from here.
}

// This function is executed by the parent process to wait for the child
// and determine its exit status.
int parent_process_wait(pid_t pid)
{
    int wstatus;
    int exit_status;

    exit_status = 1; // Default to an error status

    if (waitpid(pid, &wstatus, 0) == -1)
    {
        perror("minishell: waitpid");
        // exit_status remains 1 (or you could set a specific waitpid error status)
    }
    else
    {
        if (WIFEXITED(wstatus))
        {
            // Child exited normally, get its exit status.
            exit_status = WEXITSTATUS(wstatus);
        }
        else if (WIFSIGNALED(wstatus))
        {
            // Child was terminated by a signal.
            // Bash commonly returns 128 + signal number.
            exit_status = 128 + WTERMSIG(wstatus);
            // You might want to print a message here if a signal terminated the child,
            // e.g., if (WTERMSIG(wstatus) == SIGSEGV) printf("Segmentation fault\n");
            // but for now, just setting the status is fine.
        }
        // You could add more checks for WIFSTOPPED, WIFCONTINUED if you implement job control.
    }
    return (exit_status);
}