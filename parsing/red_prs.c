/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_prs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:44:40 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/09 23:52:01 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char	*extr_qstr(t_ptr **head, char *str)
{
	int		start;
	int		end;
	char	*quoted;
	int		i;

	start = 0;
	i = 0;
	while (str[start] && str[start] != '"' && str[start] != '\'')
		start++;
	start++;
	end = start;
	while (str[end] && str[end] != '"'&& str[end] != '\'')
		end++;
	quoted = ft_mall(head, ((end - start) + 1));
	while (start < end)
	{
		quoted[i] = str[start];
		i++;
		start++;
	}
	quoted[i] = '\0';
	return (quoted);
}

