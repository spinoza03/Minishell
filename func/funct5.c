/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allali <allali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 00:16:34 by allali            #+#    #+#             */
/*   Updated: 2025/08/02 00:17:06 by allali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	convert_to_str(char *str, unsigned int n, int *length)
{
	while (n > 0)
	{
		str[--(*length)] = (n % 10) + '0';
		n /= 10;
	}
}

static int	get_num_length(int n)
{
	int	length;

	if (n <= 0)
		length = 1;
	else
		length = 0;
	while (n != 0)
	{
		n /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				length;
	unsigned int	num;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = get_num_length(n);
	str = (char *)malloc(length + 1);
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (n == 0)
		str[0] = '0';
	else
		convert_to_str(str, num, &length);
	return (str);
}