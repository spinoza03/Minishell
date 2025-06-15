/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:49:54 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/09 14:12:01 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef enum e_builtin_id
{
    NOT_A_BUILTIN_ID = 0,
    BUILTIN_PWD,
    BUILTIN_ECHO, // For later
    BUILTIN_CD,   // For later
    BUILTIN_EXPORT, // For later
    BUILTIN_UNSET,  // For later
    BUILTIN_ENV,    // For later
    BUILTIN_EXIT    // For later
} t_builtin_id;

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
    struct s_env_copy   *next;
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
void restore_redirections(int original_fds[2]);
int apply_redirections(t_cmd *command, int original_fds[2]);
int exec_exit(t_cmd *command, t_env_copy **env_list);
int	ft_atoi(const char *str);
int	exec_unset(t_cmd *command, t_env_copy **env_list);
void env_lstdel_one(t_env_copy **list_head, const char *key);
int	exec_export(t_cmd *command, t_env_copy **env_list);
char	*ft_strchr(const char *str, int c);
int	exec_env(t_cmd *command, t_env_copy **env_list);
int	exec_cd(t_cmd *command, t_env_copy **env_list);
int	set_env_value(t_env_copy **env_list, const char *key, const char *new_value);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

int	ft_strncmp(const char *s1, const char *s2, size_t n);
int exec_echo(t_cmd *command);
int execute_external_command(const char *exec_path, t_cmd *command, char **original_envp);
void ft_free_str_array(char **array);
char	*ft_strcpy(char *dst, char *src);
char *ft_strcat(char *dst, const char *src);
char *resolve_command_path(const char *command_name, t_env_copy *env_list);
int	ft_strcmp(const char *str, const char *cmp);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char c);
char *get_env_value(t_env_copy *env_list, const char *key);
t_env_copy	*ft_lstlast(t_env_copy *lst);
void	ft_lstadd_back(t_env_copy **lst, t_env_copy *new_node);
void env_lstclear(t_env_copy **list_head);
void del_env_node_content(t_env_copy *node);
t_builtin_id get_builtin_id(const char *cmd_name);
int execute_command_controller(t_cmd *command, t_env_copy **env_list,
                                                            char **original_envp);
void	exec_builtins(char *cmd, t_env_copy **env);
int	check_builtins(char *cmd);
int	exec_pwd(t_cmd *cmd);
int	is_builtins(char *cmd, t_env_copy **env);
t_env_copy *env_lstnew(char *key_str, char *value_str);
void	ft_lstadd_front(t_env_copy **lst, t_env_copy *new);
t_env_copy	*ft_lstlast(t_env_copy *lst);
int	ft_lstsize(t_env_copy *lst);

//----------------------------------------------------------------
int	execute_builtin_command(t_builtin_id id, t_cmd *command, t_env_copy **env_list);
int execute_command_controller(t_cmd *command, t_env_copy **env_list, char **original_envp);
void	child_process_execution(const char *exec_path, char **args, char **original_envp);
int         parent_process_wait(pid_t pid);
int parent_process_wait(pid_t pid);
#endif
