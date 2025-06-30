/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:32:05 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/30 19:06:25 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void process_heredocs(t_cmd *cmd_list)
{
	t_cmd		*current_cmd;
	t_redirs	*current_redir;
	char		*temp_file;

	current_cmd = cmd_list;
	while (current_cmd)
	{
		current_redir = current_cmd->pre_redirs;
		while (current_redir)
		{
			if (current_redir->type == HEREDOC)
			{
				temp_file = handle_heredoc_read(current_redir->filename);
				free(current_redir->filename);
				current_redir->filename = temp_file;
				current_redir->type = red_in;
			}
			current_redir = current_redir->next;
		}
		// TODO: You will need to add a similar loop for post_redirs here too.
		current_cmd = current_cmd->next;
	}
}


int main(int argc, char **argv, char **envp)
{
    char        *input_line;
    t_cmd       *parsed_command;
    t_shell     shell; // Create our main struct on the stack.
    t_env_copy  *env_list_head;

    (void)argc;
    (void)argv;
    
    // --- Initialize our shell data ---
    env_list_head = NULL;
    shell.env_list = &env_list_head;
    shell.last_exit_status = 0;
    shell.child_pid = 0; // 0 means no child process is running.
    // ------------------------------------

    initialize_signals();
    create_env_list(shell.env_list, envp);
    
    while (1)
    {
        input_line = readline("minishell> ");
        if (!input_line)
        {
            printf("exit\n");
            break;
        }
        if (*input_line)
        {
            add_history(input_line);
            parsed_command = simple_parser_to_cmd(input_line);
            
            if (parsed_command)
            {
                process_heredocs(parsed_command);
                // We now pass a pointer to our 'shell' struct to the executor.
                // The executor will update shell.last_exit_status inside the struct.
                execute_pipeline(parsed_command, &shell, envp);
                free_cmd_structure(parsed_command);
            }
        }
        free(input_line);
    }

    env_lstclear(shell.env_list);
    rl_clear_history();
    return (shell.last_exit_status); // Return the final status from our struct.
}
