/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:49:54 by ilallali          #+#    #+#             */
/*   Updated: 2025/07/10 16:08:01 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <pwd.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>

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

typedef struct s_ptr
{
	void        *ptr;
	struct s_ptr *next;
}t_ptr;

typedef struct s_redirs
{
	char			*filename;
	t_tkn_type		type;
	struct s_redirs	*next;
}	t_redirs;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}t_env;

typedef struct s_cmd
{
	char			**args;
	t_redirs		*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env_copy
{
	char				*key;
	char				*value;
	struct s_env_copy	*next;
}	t_env_copy;

// NEW: Main shell data structure to avoid globals
typedef struct s_shell
{
	t_env_copy	**env_list;
	int			last_exit_status;
	pid_t		child_pid;
}	t_shell;

typedef struct s_tkn
{
	char			*vl;
	t_tkn_type		tkn_typ;
	struct s_tkn	*next;
}t_tkn;
// Enum for built-in command identification
typedef enum e_builtin_id
{
	NOT_A_BUILTIN_ID = 0,
	BUILTIN_PWD,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin_id;

// --- FUNCTION PROTOTYPES (UPDATED & INCLUDING OLD ONES) ---

// Main Setup and Loop
void		initialize_signals(void);

// Test Parser
t_cmd		*simple_parser_to_cmd(char *line_input);
void		free_cmd_structure(t_cmd *cmd_list);

// Executor Engine (The new functions with updated signatures)
int			execute_pipeline(t_cmd *cmd_list, t_shell *shell, char **original_envp);
int			execute_command_controller(t_cmd *command, t_shell *shell, char **original_envp);
int			execute_external_command(const char *exec_path, t_cmd *command, char **original_envp);
char		*resolve_command_path(const char *command_name, t_env_copy *env_list);
void    	child_process_execution(const char *exec_path, char **args, char **original_envp);
int         parent_process_wait(pid_t pid);


// Redirections
int			apply_redirections(t_cmd *command, int original_fds[2]);
void		restore_redirections(int original_fds[2]);
char		*handle_heredoc_read(const char *delimiter);

// Built-ins (New functions with updated signatures)
t_builtin_id	get_builtin_id(const char *cmd_name);
int				execute_builtin_command(t_builtin_id id, t_cmd *command, t_shell *shell);
int				exec_echo(t_cmd *command);
int				exec_pwd(t_cmd *command);
int				exec_cd(t_cmd *command, t_shell *shell);
int				exec_env(t_cmd *command, t_shell *shell);
int				exec_export(t_cmd *command, t_shell *shell);
int				exec_unset(t_cmd *command, t_shell *shell);
int				exec_exit(t_cmd *command, t_shell *shell);

// Environment and List Utilities
void		create_env_list(t_env_copy **list_head, char **envp);
void		env_lstclear(t_env_copy **list_head);
t_env_copy	*env_lstnew(char *key_str, char *value_str);
void		del_env_node_content(t_env_copy *node);
void		ft_lstadd_back(t_env_copy **lst, t_env_copy *new_node);
void		ft_lstadd_front(t_env_copy **lst, t_env_copy *new);
t_env_copy	*ft_lstlast(t_env_copy *lst);
int			ft_lstsize(t_env_copy *lst);
char		*get_env_value(t_env_copy *env_list, const char *key);
int			set_env_value(t_env_copy **env_list, const char *key, const char *new_value);
void		env_lstdel_one(t_env_copy **list_head, const char *key);

// Utility Functions
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *str);
int 		ft_strncmp(const char *s1, const char *s2, size_t n);
void    	ft_putstr_fd(char *s, int fd);
void    	ft_putchar_fd(char c, int fd);
char 		*ft_strcat(char *dst, const char *src);
char    	*ft_strcpy(char *dst, char *src);
void ft_free_str_array(char **array);
void	*ft_memcpy(void *dst, const void *src, size_t n);

void initialize_signals(void);
void sigint_handler(int signum);

/* FUNCTIONS */
int	ft_isalpha(int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	cleanup_heredocs(t_cmd *cmd_list);
void	print_cmd_list_debug(t_cmd *cmd_list);;
int	process_heredocs(t_cmd *cmd_list);
int	execute_single_heredoc(t_redirs *redir);
void handle_heredoc_read_child(const char *delimiter, const char *temp_filename);
void	set_execution_signals(void);
int handle_redir_in(const char *filename);
//------------------parsing mohsin----------------------------------------------------------------
int	    	ft_atoi1(const char *str);
size_t		ft_strlen(const char *s);
char		*ft_strjoin1(t_ptr **head, char const *s1, char const *s2);
char		*ft_strdup1(t_ptr **head, const char *s);
void		*ft_memcpy1(void *dest, const void *src, size_t n);
void		add_node(t_ptr **head, void *ptr);
void    	*ft_mall(t_ptr **head, ssize_t size);
void		ft_lstadd_back1(t_ptr **lst, t_ptr *new);
void		ft_lstclear1(t_ptr **lst, void (*del)(void*));
/*parsing starting*/
t_cmd		*pars(t_ptr **head, char *input, char **env); //added env for the test
int			check_q(char *input, int i);
int			checker_synx(char *input, char check);
int			first_q(char *input);
void		ft_putstr_fd(char *s, int fd);
int	    	invalid_sqnc(char *input);
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

#endif
