/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:32:05 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/09 15:48:00 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int g_last_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
    char        *input_line;
    t_cmd       *parsed_command;
    t_env_copy  *shell_env_list; // Changed from 'head' for clarity

    (void)argc;
    (void)argv;
    shell_env_list = NULL; // Important to initialize to NULL
    create_env_list(&shell_env_list, envp);
    while (1)
    {
        input_line = readline("minishell> "); // Prompt

        if (!input_line) // Ctrl-D pressed (EOF)
        {
            printf("exit\n"); // Mimic bash behavior for Ctrl-D
            break;
        }
        if (*input_line) // If the input is not empty
        {
            add_history(input_line); // History
            parsed_command = simple_parser_to_cmd(input_line);

            if (parsed_command)
            {
                if (parsed_command->args && parsed_command->args[0])
                {
                    g_last_exit_status = execute_command_controller(parsed_command,
                                                                 &shell_env_list, envp);
                }
                else if (!parsed_command->args) // Parser returned a command struct but no args array (e.g. only redirections)
                {

                }
                free_cmd_structure(parsed_command);
            }
        }
        free(input_line); // Free the line read by readline
    }
    env_lstclear(&shell_env_list);
    rl_clear_history(); // Allowed function
    return (g_last_exit_status); // Exit with the status of the last command
}
