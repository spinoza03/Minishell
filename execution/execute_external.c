/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 23:58:23 by allali            #+#    #+#             */
/*   Updated: 2025/06/30 18:33:38 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int handle_external_command(t_cmd *command, t_shell *shell,
                                                        char **original_envp)
{
    char    *executable_path;
    int     exit_status;

    executable_path = resolve_command_path(command->args[0], *(shell->env_list));
    if (executable_path)
    {
        // We must save the return value from the function that forks and waits.
        exit_status = execute_external_command(executable_path, command, original_envp);
        free(executable_path);
    }
    else
    {
        // This part for "command not found" is correct.
        write(2, "minishell: ", 11);
        write(2, command->args[0], ft_strlen(command->args[0]));
        write(2, ": command not found\n", 20);
        exit_status = 127;
    }
    return (exit_status);
}

// This is the main controller function.
// It is called from inside a forked child process for commands like `echo > file`
// or `ls > file`. Its only job is to figure out what command to run.
int execute_command_controller(t_cmd *command, t_shell *shell,
                                                            char **original_envp)
{
    t_builtin_id    builtin_id;
    int             dummy_fds[2];

    // STEP 1: Apply file redirections. This happens INSIDE the child.
    if (apply_redirections(command, dummy_fds) != 0)
        exit(1); // If a file can't be opened, the child process must exit.

    // If there are no arguments after redirection (e.g., just "> out"), exit successfully.
    if (!command->args || !command->args[0])
        exit(0);

    // STEP 2: Figure out what command to run.
    builtin_id = get_builtin_id(command->args[0]);
    if (builtin_id != NOT_A_BUILTIN_ID)
    {
        // It's a "fork-safe" built-in like `echo` or `pwd`.
        // We run it and return its status.
        return (execute_builtin_command(builtin_id, command, shell));
    }
    else
    {
        // It's an external command like `ls`.
        // This will call execve and will not return if successful.
        return (handle_external_command(command, shell, original_envp));
    }
}