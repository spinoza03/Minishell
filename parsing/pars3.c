/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:09:53 by mteffahi          #+#    #+#             */
/*   Updated: 2025/06/16 18:53:51 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cpy(char *vl, char *input, int pos, int len)
{
	int	tmp;

	tmp = 0;
	while (tmp < len)
	{
		vl[tmp] = input[pos + tmp];
		tmp++;
	}
	vl[tmp] = '\0';
}

int	splt_quoted(t_ptr **head, t_tkn **token, char *input, int *i)
{
	int			len;
	char		*vl;
	int			pos;
	char		q_type;

	if (!input)
		return (ft_mall(head, 0), 0);
	q_type = input[*i];
	(*i)++;
	len = 0;
	pos = *i;
	while (input[*i] && input[*i] != q_type)
	{
		(*i)++;
		len++;
	}
	if (input[*i] == q_type)
		(*i)++;  // Skip closing quote
	if (len == 0 && (*i) >= 2 && input[(*i) - 3] != '=')
		return (ft_putstr_fd("cat: '': No such file or directory\n", 2), 0);
	vl = ft_mall(head, (len + 1));
	cpy(vl, input, pos, len);
	creat_tkn_node(head, token, vl, identify_tkn(vl));
	return (0);
}

char	*gt_nm(char *input, int *i, t_ptr **head)
{
	int		pos;
	int		len;
	char	*v_name;

	pos = *i;
	len = 0;
	while (input[pos] && ft_isalnum(input[pos]))
	{
		pos++;
		len++;
	}
	v_name = ft_mall(head, (len + 1));
	pos = 0;
	while (input[*i] && ft_isalnum(input[*i]) && pos < len)
	{
		v_name[pos] = input[*i];
		pos++;
		(*i)++;
	}
	v_name[len] = '\0';
	return (v_name);
}

int	expand_var(char *input, int *i, t_tkn **tkn_head, t_ptr **head_ptr)
{
	const char *env;
	const char	*nm;

	(*i)++;
	nm = gt_nm(input, i, head_ptr);
	env = ft_strdup(head_ptr, getenv(nm));
	if (!env)
	{
		(*i)++;
		ft_mall(head_ptr, 0);
		return (ft_putstr_fd("\n", 1), 0);
	}
	creat_tkn_node(head_ptr, tkn_head, (char *)env, identify_tkn(((char *)env)));
	// (*i)++;
	return (1);
}
