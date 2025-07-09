/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:30:55 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/09 15:26:58 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <pwd.h>
# include <sys/types.h>
# include <unistd.h>
# define LL_MAX 9223372036854775807LL

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}t_env;


typedef struct s_ptr
{
	void        *ptr;
	struct s_ptr *next;
}t_ptr;

typedef enum e_tkn_type
{
	NULL_Tk,	// 0
	wrd,		// 1
	PI,		// |	2
	red_in,		// <	3
	red_out,	// >	4
	red_apnd,	// >>	5
	HEREDOC		// <<	6
}t_tkn_type;

typedef struct s_tkn
{
	char			*vl;
	t_tkn_type		tkn_typ;
	struct s_tkn	*next;
}t_tkn;

// typedef enum e_tkn_type
// {
// 	red_in,
// 	red_out,
// 	red_apnd,
// 	HEREDOC
// }	t_tkn_type;

typedef struct s_redirs
{
	char			*filename;
	t_tkn_type		type;
	struct s_redirs	*next;
}	t_redirs;

typedef struct s_cmd
{
	char			**args;
	t_redirs		*pre_redirs;
	t_redirs		*post_redirs;
	struct s_cmd	*next;
}	t_cmd;


int	    	ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(t_ptr **head, char const *s1, char const *s2);
char		*ft_strdup(t_ptr **head, const char *s);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		add_node(t_ptr **head, void *ptr);
void    	*ft_mall(t_ptr **head, ssize_t size);
void		ft_lstadd_back(t_ptr **lst, t_ptr *new);
void		ft_lstclear(t_ptr **lst, void (*del)(void*));
/*parsing starting*/
void		pars(t_ptr **head, char *input, char **env); //added env for the test
int			check_q(char *input, int i);
int			checker_synx(char *input, char check);
int			first_q(char *input);
void		ft_putstr_fd(char *s, int fd);
int	    	invalid_sqnc(char *input);
int 		ft_strcmp(char *s1, char *s2);
/**********************************************************************************************/
int			is_qtd(char *input);
void		ft_lstadd_back_tkn(t_tkn **lst, t_tkn *new);
t_tkn_type	identify_tkn(char *val);
int			splt_quoted(t_ptr **head, t_tkn **token, char *input, int *i);
int			splt(t_ptr **head, t_tkn **token, char *input, int *i);
void		creat_tkn_node(t_ptr **head, t_tkn **tkn_head, char *val, t_tkn_type type);
/**********************************************************************************************/
int 		handle_rdr(t_ptr **head, t_tkn **token, char *input, int *i);
/**********************************************************************************************/
int			expand_var(char *input, int *i, t_tkn **tkn_head, t_ptr **head_ptr);
int			ft_isalnum(int c);
char		*gt_nm(char *input, int *i, t_ptr **head);
/**********************************************************************************************/
						/*for setting the envirment to a singly linked list*/
void		ft_lstadd_back_env(t_env **lst, t_env *new);
t_env		*set_env_ls(t_ptr **head_ptr, char **env);
void		set_node(t_env **head, t_ptr **ptr_head, char *env_val);
/************************** getting var name **************************************************/
char		*get_vr(t_env **head, t_ptr **head_ptr, char *name);
char		*extract_vl(t_ptr **ptr_head, char *variable);
int 		ft_strcmp_vr(char *s1, char *s2, size_t size);
/************************** creating the cmd **************************************************/
t_cmd		*parse_tokens_to_commands(t_ptr **head, t_tkn *tokens);
t_cmd		*crt_cmd(t_ptr **ptr);
/////////////////////////////////////////////////////////////////////////////////
void		append_arg(t_ptr **head, char ***args, char *word);
void append_redir(t_redirs **list, t_redirs *new_redir);
t_cmd *init_new_cmd(t_ptr **head);
//////////////////	FOR PRINTING	/////////////////////////////////////////////
void print_cmd_list(t_cmd *cmd_list);
void print_redirs(t_redirs *redir_list, const char *label);

#endif
