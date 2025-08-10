/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:51:18 by ilallali          #+#    #+#             */
/*   Updated: 2025/08/10 19:23:52 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	get_final_status(int last_status)
{
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
	{
		if (WTERMSIG(last_status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
		return (128 + WTERMSIG(last_status));
	}
	return (last_status);
}

static int	wait_for_pipeline(pid_t last_pid, int cmd_count)
{
	int		status;
	int		last_status;
	pid_t	waited_pid;

	last_status = 0;
	while (cmd_count > 0)
	{
		waited_pid = wait(&status);
		if (waited_pid == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (waited_pid == last_pid)
			last_status = status;
		cmd_count--;
	}
	return (get_final_status(last_status));
}

static void	child_in_pipe(t_cmd *cmd, t_shell *shell, char **envp, t_fds *fds)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (fds->in != STDIN_FILENO)
	{
		dup2(fds->in, STDIN_FILENO);
		close(fds->in);
	}
	if (fds->out != STDOUT_FILENO)
	{
		close(fds->pipe[0]);
		dup2(fds->out, STDOUT_FILENO);
		close(fds->out);
	}
	exit(execute_command_controller(cmd, shell, envp));
}

static pid_t	execute_pipeline_loop(t_cmd *cmd_list, t_shell *shell,
										char **original_envp)
{
	pid_t	last_pid;
	t_fds	fds;

	fds.in = STDIN_FILENO;
	last_pid = -1;
	while (cmd_list)
	{
		if (cmd_list->next && pipe(fds.pipe) == -1)
			return (perror("minishell: pipe"), -1);
		if (cmd_list->next)
			fds.out = fds.pipe[1];
		else
			fds.out = STDOUT_FILENO;
		last_pid = fork();
		if (last_pid < 0)
			return (perror("minishell: fork"), -1);
		if (last_pid == 0)
			child_in_pipe(cmd_list, shell, original_envp, &fds);
		parent_setup_pipes(&fds, cmd_list);
		cmd_list = cmd_list->next;
	}
	return (last_pid);
}

int	execute_pipeline(t_cmd *cmd_list, t_shell *shell,
						char **original_envp)
{
	pid_t			last_pid;
	t_cmd			*head;
	t_builtin_id	builtin_id;
	int				original_fds[2];

	head = cmd_list;
	if (cmd_list->args && cmd_list->args[0])
		builtin_id = get_builtin_id(cmd_list->args[0]);
	else
		builtin_id = NOT_A_BUILTIN_ID;
	if (cmd_list->next == NULL && is_parent_builtin(builtin_id))
	{
		apply_redirections(cmd_list, original_fds);
		shell->last_exit_status = execute_builtin_command(builtin_id,
				cmd_list, shell);
		restore_redirections(original_fds);
		return (shell->last_exit_status);
	}
	set_execution_signals();
	last_pid = execute_pipeline_loop(head, shell, original_envp);
	if (last_pid == -1)
		return (1);
	shell->last_exit_status = wait_for_pipeline(last_pid, count_commands(head));
	initialize_signals();
	return (shell->last_exit_status);
}
