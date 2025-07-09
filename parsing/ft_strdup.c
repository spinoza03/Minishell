/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:19:32 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/09 15:27:17 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(t_ptr **head, const char *s)
{
	size_t	size;
	char	*result;

	if (!s)
		return(NULL);
	size = ft_strlen(s) + 1;
	result = ft_mall(head, size);
	if (!result)
		return (NULL);
	ft_memcpy(result, s, ft_strlen(s));
	result[ft_strlen(s)] = '\0';
	return (result);
}
