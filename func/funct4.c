/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:24:49 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/14 17:25:12 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;
	long	tmp;

	sign = 1;
	result = 0;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tmp = result;
		result = result * 10 + (*str - '0');
		if (tmp != result / 10 && sign == 1)
			return (-1);
		else if (tmp != result / 10 && sign == -1)
			return (0);
		str++;
	}
	return (sign * result);
}