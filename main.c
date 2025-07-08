/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:32:05 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/08 18:21:05 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


static void	init_shell(t_shell *shell, t_env_copy **env_list_head, char **envp)
{
	*env_list_head = NULL;
	shell->env_list = env_list_head;
	shell->last_exit_status = 0;
	shell->child_pid = 0;
	initialize_signals();
	create_env_list(shell->env_list, envp);
}

// Helper 2: This function remains unchanged.
static void	process_input_line(char *line, t_shell *shell, char **envp)
{
	t_cmd	*parsed_command;
	int		heredoc_interrupted;

	add_history(line);
	parsed_command = simple_parser_to_cmd(line);
	if (parsed_command)
	{
		heredoc_interrupted = process_heredocs(parsed_command);
		if (heredoc_interrupted == 0)
			execute_pipeline(parsed_command, shell, envp);
		free_cmd_structure(parsed_command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input_line;
	t_shell		shell;
	t_env_copy	*env_list_head;

	(void)argc;
	(void)argv;
	init_shell(&shell, &env_list_head, envp);
	while (1)
	{
		input_line = readline("minishell> ");
		if (!input_line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*input_line)
			process_input_line(input_line, &shell, envp);
		free(input_line);
	}
	env_lstclear(shell.env_list);
	rl_clear_history();
	return (shell.last_exit_status);
}
