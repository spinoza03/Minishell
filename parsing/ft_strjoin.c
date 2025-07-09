/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:10:42 by mteffahi          #+#    #+#             */
/*   Updated: 2025/07/09 15:57:43 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(t_ptr **head, char const *s1, char const *s2)
{
	char	*result;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	if (s1[0] == '\0' && s2[0] == '\0')
		return (ft_strdup(head, ""));
	if (s1[0] == '\0')
		return (ft_strdup(head ,s2));
	if (s2[0] == '\0')
		return (ft_strdup(head ,s1));
	size = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	result = ft_mall(head, size);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, ft_strlen(s1));
	ft_memcpy(result + ft_strlen(s1), s2, ft_strlen(s2));
	result[size - 1] = '\0';
	return (result);
}
