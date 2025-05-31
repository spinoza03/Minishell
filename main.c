/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:32:05 by ilallali          #+#    #+#             */
/*   Updated: 2025/05/31 16:47:11 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int main(int argc, char **argv, char **envp)
{
    char    *input_line;
    t_cmd   *parsed_command;
	t_env_copy *head;

    // Silence unused argc/argv warnings for now
    (void)argc;
    (void)argv;
	create_env_list(head, envp);
	
    // from your creat_env.c

    while (1)
    {
        input_line = readline("minishell-sim> "); // Changed prompt for clarity
        if (!input_line) // Ctrl-D pressed (EOF)
        {
            printf("exit\n"); // Mimic bash behavior
            break;
        }

        if (*input_line) // If the input is not empty
        {
            add_history(input_line);

            // Basic "exit" command check (will be a proper builtin later)
            if (strcmp(input_line, "exit") == 0)
            {
                free(input_line);
                break;
            }

            // 1. Parse the input line using our simple internal parser
            parsed_command = simple_parser_to_cmd(input_line);

            if (parsed_command)
            {
                // 2. Execute the command
                // For this test, parsed_command->args[0] must be an absolute path
                // e.g., you type: "/bin/ls -l" or "/bin/echo hello"
                if (parsed_command->args && parsed_command->args[0])
                {
                    execute_this_one_command(parsed_command->args, envp);
                }
                else
                {
                    // This case should ideally not be reached if simple_parser_to_cmd
                    // returns NULL for empty/invalid args.
                    // fprintf(stderr, "minishell: No command to execute after parsing.\n");
                }
                
                // 3. Free the command structure
                free_cmd_structure(parsed_command);
            }
        }
        free(input_line); // Free the line read by readline
    }

    // rl_clear_history(); // Optional: clear readline history on exit
    return (0); // Or the last command's exit status
}
