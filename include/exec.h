/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:49:54 by ilallali          #+#    #+#             */
/*   Updated: 2025/05/25 18:36:08 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef enum e_tkn_type
{
    NULL_Tk,    // 0
    wrd,        // 1
    PI,        // |    2
    red_in,        // <    3
    red_out,    // >    4
    red_apnd,    // >>    5
    HEREDOC        // <<    6
}t_tkn_type;

typedef struct s_tkn
{
    char            *vl;
    t_tkn_type        tkn_typ;
    struct s_tkn    *next;
}t_tkn;

typedef struct s_cmd
{
	char **args;          // command and its arguments: ["echo", "hello", NULL]
	char *infile;         // for '<'
	char *outfile;        // for '>' or '>>'
	int append;           // 1 if '>>', 0 if '>'
	int heredoc;          // 1 if '<<'
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
#endif
