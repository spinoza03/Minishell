/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:12:05 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/15 20:21:01 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int    invalid_sqnc(char *input)
{
	int size;

	size = ft_strlen(input) - 1;
	if (input[0] == '|' || input[size] == '|')
		return (ft_putstr_fd("syntax error near unexpected token\n", 2), 0);
	return (1);
}

int	is_qtd(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"' || input[i] == '\'')
			return (1);
	}
	return (0);
}
