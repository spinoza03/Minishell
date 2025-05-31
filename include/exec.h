/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:49:54 by ilallali          #+#    #+#             */
/*   Updated: 2025/05/31 11:51:42 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define HER 1
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

t_cmd *token_to_cmd(t_tkn *tokens);
void append_token(t_tkn **head, char *val, t_tkn_type type);
t_tkn *mock_tokens(char *line);
#endif
