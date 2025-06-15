/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:09:57 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/14 19:33:36 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
	{
		l++;
	}
	return (l);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*des;
	unsigned char		*str;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	des = (unsigned char *)dst;
	str = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		des[i] = str[i];
		i++;
	}
	return (dst);
}
int	ft_strcmp(const char *str, const char *cmp)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] == cmp[i])
		i++;
	return ((unsigned char)str[i] - (unsigned char)cmp[i]);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		else
			i++;
	}
	return (NULL);
}

char *ft_strcat(char *dst, const char *src)
{
    size_t  dst_idx; // To find the end of dst
    size_t  src_idx; // To iterate through src

    dst_idx = 0;
    while (dst[dst_idx])
        dst_idx++;
    src_idx = 0;
    while (src[src_idx])
    {
        dst[dst_idx] = src[src_idx];
        dst_idx++;
        src_idx++;
    }
    dst[dst_idx] = '\0';
    return (dst);
}
