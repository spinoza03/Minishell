/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:32:05 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/10 15:01:53 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"      // Your header with executor prototypes

static void	init_shell(t_shell *shell, t_env_copy **env_list_head, char **envp)
{
	*env_list_head = NULL;
	shell->env_list = env_list_head;
	shell->last_exit_status = 0;
	shell->child_pid = 0;
	initialize_signals();
	create_env_list(shell->env_list, envp);
}

// Processes a single line of input.
static void	process_input(char *line, t_shell *shell, char **envp)
{
	t_ptr	*memory_head;
	t_cmd	*command_list;

	memory_head = NULL;
	add_history(line);
	command_list = pars(&memory_head, line, envp);
	
	if (command_list)
	{
		if (process_heredocs(command_list) == 0)
			execute_pipeline(command_list, shell, envp);
		cleanup_heredocs(command_list);
	}
	ft_mall(&memory_head, -1);
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
			process_input(input_line, &shell, envp);
		free(input_line);
	}
	env_lstclear(shell.env_list);
	rl_clear_history();
	return (shell.last_exit_status);
}