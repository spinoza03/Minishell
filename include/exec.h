/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:49:54 by ilallali          #+#    #+#             */
/*   Updated: 2025/05/31 16:46:23 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef enum e_tkn_type
{      
    red_in,    // < 
	red_out,    // >    1
    red_apnd,    // >>    2
    HEREDOC        // <<    3
}t_tkn_type;


typedef struct s_redirs
{
	char *filename;
	t_tkn_type type;
    struct s_redirs    *next;
}t_redirs;


typedef struct s_cmd
{
	char 		**args;          // command and its arguments: ["echo", "hello", NULL]
	t_redirs 	*pre_redirs;
	t_redirs 	*post_redirs;
	struct s_cmd *next;   // for pipelines (| command | command | ...)
} t_cmd;

typedef struct s_env_copy {
    char                *key;   // Variable name (e.g., "PATH")
    char                *value; // Variable value (e.g., "/usr/bin:/bin")
    struct s_env_node   *next;
} t_env_copy;

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

t_cmd   *simple_parser_to_cmd(char *line_input);
t_cmd   *new_cmd_for_parser(void);
void    execute_this_one_command(char **args, char **envp);
void    free_cmd_structure(t_cmd *cmd);
void create_env_list(t_env_copy **list_head, char **envp);

/* FUNCTIONS */
void	ft_lstadd_back(t_env_copy **lst, t_env_copy *new_node);
void	ft_lstadd_front(t_env_copy **lst, t_env_copy *new);
t_env_copy	*ft_lstlast(t_env_copy *lst);
int	ft_lstsize(t_env_copy *lst);
void	ft_lstadd_back(t_env_copy **lst, t_env_copy *new_node);

#endif
