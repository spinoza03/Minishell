/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:32:05 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/08 13:49:05 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


static void handle_heredoc_read_child(const char *delimiter, const char *temp_filename)
{
    char    *line;
    int     fd;

    signal(SIGINT, SIG_DFL); // Reset Ctrl-C to default for the child
    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
        exit(1);
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    exit(0);
}

static int process_heredocs(t_cmd *cmd_list)
{
    t_cmd       *current_cmd;
    t_redirs    *redir;
    pid_t       pid;
    int         status;

    current_cmd = cmd_list;
    while (current_cmd)
    {
        redir = current_cmd->redirs;
        while (redir)
        {
            if (redir->type == HEREDOC)
            {
                pid = fork();
                if (pid == 0)
                    handle_heredoc_read_child(redir->filename, "/tmp/heredoc_tmp");
                waitpid(pid, &status, 0);
                if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
                    return (1); // Interrupted, return 1
                free(redir->filename);
                redir->filename = ft_strdup("/tmp/heredoc_tmp");
                redir->type = red_in;
            }
            redir = redir->next;
        }
        current_cmd = current_cmd->next;
    }
    return (0); // Success, return 0
}

int main(int argc, char **argv, char **envp)
{
    char        *input_line;
    t_cmd       *parsed_command;
    t_shell     shell;
    t_env_copy  *env_list_head;
    int         heredoc_interrupted;

    (void)argc;
    (void)argv;
    env_list_head = NULL;
    shell.env_list = &env_list_head;
    shell.last_exit_status = 0;
    shell.child_pid = 0;
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
                heredoc_interrupted = process_heredocs(parsed_command);
                if (heredoc_interrupted == 0)
                    execute_pipeline(parsed_command, &shell, envp);
                free_cmd_structure(parsed_command);
            }
        }
        free(input_line);
    }
    env_lstclear(shell.env_list);
    rl_clear_history();
    return (shell.last_exit_status);
}
