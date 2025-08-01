/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:39:06 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/21 17:57:10 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	checker_synx(char *input, char check)
{
	int	cnt;
	int	i;

	i = -1;
	cnt = 0;
	while (input[++i])
	{
		if (input[i] == check)
			cnt++;
	}
	if (cnt > 0 && cnt % 2 == 0)
		return (1);
	else
		return (0);
}

static int	check_q_helper(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == ')')
			return (1);
		i++;
	}
	return (0);
}

int	check_q(char *input, int i)
{
	if (input[i] == '\'')
		return (checker_synx(input, '\''));
	else if (input[i] == '"')
		return (checker_synx(input, '"'));
	else if (input[i] == '(')
		return (check_q_helper(input, i));
	return (57);
}

int	first_q(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"' || input[i] == '(')
		{
			// if (input[i + 1] == '\'' || input[i + 1] == '"' || input[i + 1] == ')')
				// return (ft_putstr_fd("cat: '': No such file or directory", 2), 0);
			if (!(check_q(input, i)))
				return (ft_putstr_fd("Syntax error\n", 2), 0);
		}
	}
	return (1);
}

void	creat_tkn_node(t_ptr **head, t_tkn **tkn_head, char *val, t_tkn_type type)
{
	t_tkn	*node;

	node = ft_mall(head, sizeof(t_tkn));
	node->vl = val;
	node->tkn_typ = type;
	node->next = NULL;
	ft_lstadd_back_tkn(tkn_head, node);
}

t_tkn_type identify_tkn(char *val)
{
	if (!val || !*val)
		return (NULL_Tk);
	else if (ft_strcmp(val, "|") == 0)
		return (PI);
	else if (ft_strcmp(val, ">") == 0)
		return (red_out);
	else if (ft_strcmp(val, "<") == 0)
		return (red_in);
	else if (ft_strcmp(val, ">>") == 0)
		return (red_apnd);
	else if (ft_strcmp(val, "<<") == 0)
		return (HEREDOC);
	else
		return (wrd);
}

int handle_rdr(t_ptr **head, t_tkn **token, char *input, int *i)
{
	char *vl;
	t_tkn_type type;
	
	if (input[*i] == '|')
	{
		vl = ft_mall(head, 2);
		vl[0] = '|';
		vl[1] = '\0';
		(*i)++;
		type = identify_tkn(vl);
		creat_tkn_node(head, token, vl, type);
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			vl = ft_mall(head, 3);
			vl[0] = '<';
			vl[1] = '<';
			vl[2] = '\0';
			(*i) += 2;
			type = identify_tkn(vl);
			creat_tkn_node(head, token, vl, type);
		}
		else
		{
			vl = ft_mall(head, 2);
			vl[0] = '<';
			vl[1] = '\0';
			(*i)++;
			type = identify_tkn(vl);
			creat_tkn_node(head, token, vl, type);
		}
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			vl = ft_mall(head, 3);
			vl[0] = '>';
			vl[1] = '>';
			vl[2] = '\0';
			(*i) += 2;
			type = identify_tkn(vl);
			creat_tkn_node(head, token, vl, type);
		}
		else
		{
			vl = ft_mall(head, 2);
			vl[0] = '>';
			vl[1] = '\0';
			(*i)++;
			type = identify_tkn(vl);
			creat_tkn_node(head, token, vl, type);
		}
	}
	return (0);
}

int	splt(t_ptr **head, t_tkn **token, char *input, int *i)
{
	int			len;
	char		*vl;
	int			pos;
	t_tkn_type	type;

	if (!input)
		return (ft_mall(head, 0), 0);
	len = 0;
	pos = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\'' && input[*i] != '"'
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>' && input[*i] != '$')
	{
		(*i)++;
		len++;
	}
	// printf("inp = %c", input[*i]);
	if (input[*i] == '$')
		return (1);
	vl = ft_mall(head, (len + 1));
	len = 0;
	while (pos < *i)
	{
		vl[len] = input[pos];
		pos++;
		len++;
	}
	vl[len] = '\0';
	type = identify_tkn(vl);
	creat_tkn_node(head, token, vl, type);
	// (*i)++;
	return (0);
}

// static void	printi_zab(t_tkn **head)
// {
// 	t_tkn	*tmp;
// 	int		i;

// 	i = 0;
// 	tmp = *head;
// 	while (tmp)
// 	{
// 		printf("token value %s , token type %d, token index %d", tmp->vl, tmp->tkn_typ, i);
// 		i++;
// 		tmp = tmp->next;
// 	}
// }


void	ft_putnbr(int nbr)
{
	if (nbr < 0)
	{
		nbr *= -1;
		write(1, "-", 1);
		ft_putnbr(nbr);
	}
	else if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
		write(1, &(char){nbr + '0'}, 1);
}

void shell_last_exit(char *input,int *i, int shell_last_exit)
{
	// printf("%d", shell_last_exit);
	ft_putnbr(shell_last_exit);
	if (ft_strlen(input) == 2 && input[0] == '$' && input[1] == '?')
		ft_putchar_fd('\n', 1);
	(*i) += 2;
}

int little_check(char *input)
{
	if (input[0] == '\"' && input[1] == '\"')
		return (0);
	else
		return (1);
}

char *cpy_input(t_ptr **head, char *input)
{
    int total_len = 0;
    int non_whitespace_count = 0;
    int i, j;
    char *result;// echo	hi
    
    while (input[total_len])
    {
        if (!(input[total_len] >= 9 && input[total_len] <= 13))
            non_whitespace_count++;
        total_len++;
    }
    result = ft_mall(head, non_whitespace_count + 1);
    i = 0;
    j = 0;
    while (input[i])
    {
        if (!(input[i] >= 9 && input[i] <= 13))
        {
            result[j] = input[i];
            j++;
        }
        i++;
    }
    result[j] = '\0';
    return (result);
}

int	last_pipe_check(t_tkn **head)
{
	t_tkn	*tmp;

	if (!*head)
		return (0);
	tmp = *head;
	while (tmp)
	{
		if (tmp->tkn_typ == 2)
		{
			if (tmp->next && tmp->next->tkn_typ == 2)
				return (ft_putstr_fd("syntax error near unexpected token `|'\n", 1), 0);
		}
		tmp = tmp->next;
	}
	return (1);
}


void get_shell_pid_str(t_ptr **head, int *pos)
{
    int fd = open("/proc/self/stat", O_RDONLY);
    if (fd == -1)
	{
		(*pos) += 1;
        return ;
	}
	
    char buf[128];
    ssize_t bytes = read(fd, buf, sizeof(buf) - 1);
    close(fd);
    if (bytes <= 0)
	{
		(*pos) += 1;
		return ;
	}
	
    buf[bytes] = '\0';
	
    // Extract PID: it's the first field, space-delimited
    int i = 0;
    while (buf[i] && buf[i] != ' ')
	i++;

    char *pid_str = ft_mall(head, (i + 1));
    // if (!pid_str)
    //     return NULL;
    for (int j = 0; j < i; j++)
	pid_str[j] = buf[j];
    pid_str[i] = '\0';
	
	(*pos) += 1;
	ft_putstr_fd(pid_str, 1);
	ft_putstr_fd(": command not found\n", 1);
    // return pid_str;
}

t_cmd	*pars(int last_exit_status, t_ptr **head, char *inp, t_env_copy **env_hd)
{
	int		i;
	t_tkn	*tkn_head;
	t_cmd	*final_cmd_list;
	// t_env	*env_hd; // This seems unused for now
	char	*input;

	tkn_head = NULL;
	final_cmd_list = NULL;
	// env_hd = NULL;
	// env_hd = set_env_ls(head, env);
	input = cpy_input(head, inp);
	if (!input || !first_q(input) || !invalid_sqnc(input))
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (input[i] && input[i] == ' ')
			i++;
		else if (input[i] && (input[i] == '\'' || input[i] == '"'))
			splt_quoted(head, &tkn_head, input, &i);
		else if (input[i] && (input[i] == '|' || input[i] == '<' || input[i] == '>'))
			handle_rdr(head, &tkn_head, input, &i);
		else if (input[i] && (input[i] == '$' && input[i + 1] == '$'))
		{
			get_shell_pid_str(head, &i);
			break ;
		}
		else if (input[i] == '$' && input[i + 1] == '?')
			shell_last_exit(input, &i, last_exit_status);
		else if (input[i] && input[i] == '$')
		{
			i++;
			char *whole_vr = get_vr(env_hd, head, gt_nm(input, &i, head));
			printf("whole %s\n", whole_vr);
			// char *val = extract_vl(head, env_hd, whole_vr); // not needed anymore
			creat_tkn_node(head, &tkn_head, whole_vr, identify_tkn(whole_vr));
		}
		else if (input[i])
			splt(head, &tkn_head, input, &i);
	}
	if (!last_pipe_check(&tkn_head))
		return (NULL);
	final_cmd_list = parse_tokens_to_commands(head, tkn_head);
	// printi_zab(&tkn_head);
	return (final_cmd_list); // Return the final list
}
