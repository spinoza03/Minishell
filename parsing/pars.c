/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:39:06 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/05 22:05:14 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				// return (ft_putstr_fd("cat: '': No such file or directory\n", 2), 0);
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
	// printf("inp = %c\n", input[*i]);
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

static void	printi_zab(t_tkn **head)
{
	t_tkn	*tmp;
	int		i;

	i = 0;
	tmp = *head;
	while (tmp)
	{
		printf("token value %s , token type %d, token index %d\n", tmp->vl, tmp->tkn_typ, i);
		i++;
		tmp = tmp->next;
	}
}

void	pars(t_ptr **head,char *input, char **env)
{
	int		i;
	t_tkn	*tkn_head;
	t_env	*env_hd;

	tkn_head = NULL;
	env_hd = NULL;
	env_hd = set_env_ls(head, env);
	// if (!input)
	// 	return ;
	if (!input || !first_q(input) || !invalid_sqnc(input))
		return ;
	i = 0;
	while (input[i])
	{
		if (input[i] && input[i] == ' ')
			i++;  // Skip spaces
		else if (input[i] && (input[i] == '\'' || input[i] == '"'))
			splt_quoted(head, &tkn_head, input, &i);
		else if (input[i] && (input[i] == '|' || input[i] == '<' || input[i] == '>'))
			handle_rdr(head, &tkn_head, input, &i);
		else if (input[i] && input[i] == '$')
		{
			// if (!(expand_var(input, &i, &tkn_head, head)))
				// break ;
			i++;
			char *whole_vr = get_vr(&env_hd, head, gt_nm(input, &i, head));
			char *val = extract_vl(head, whole_vr);
			creat_tkn_node(head, &tkn_head, val, identify_tkn(val));
		}
		else if (input[i])
			splt(head, &tkn_head, input, &i);
	}
	printi_zab(&tkn_head);
	t_cmd *final = parse_tokens_to_commands(head, tkn_head);
	print_cmd_list(final);
}
