/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:32:05 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/06 16:50:15 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


static void handle_heredoc_read_child(const char *delimiter, const char *temp_filename)
{
    char    *line;
    int     fd;

    // Reset Ctrl-C to its default behavior for the heredoc reader
    signal(SIGINT, SIG_DFL);

    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
        exit(1); // Exit child with error status
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
    exit(0); // Exit child successfully
}

static void process_heredocs(t_cmd *cmd_list)
{
    t_cmd       *current_cmd;
    t_redirs    *current_redir;
    char        *temp_file;
    pid_t       pid;
    int         status;

    current_cmd = cmd_list;
    while (current_cmd)
    {
        current_redir = current_cmd->pre_redirs;
        while (current_redir)
        {
            if (current_redir->type == HEREDOC)
            {
                // Create a temporary filename.
                temp_file = ft_strdup("/tmp/minishell_heredoc");
                // Fork before reading the heredoc.
                pid = fork();
                if (pid == 0)
                {
                    // CHILD: Reads the heredoc and exits.
                    handle_heredoc_read_child(current_redir->filename, temp_file);
                }
                // PARENT: Waits for the child to finish.
                waitpid(pid, &status, 0);
                // Now, transform the node into a simple input redirection.
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

    // initialize_signals();
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
