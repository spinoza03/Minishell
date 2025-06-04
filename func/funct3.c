/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:26:49 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/04 18:22:32 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char	*ft_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

void ft_free_str_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
}
