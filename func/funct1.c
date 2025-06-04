/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilallali <ilallali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:07:57 by ilallali          #+#    #+#             */
/*   Updated: 2025/06/03 16:16:28 by ilallali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*get_next_word(const char **s, char c)
{
	const char	*start;
	size_t		len;
	char		*word;

	while (**s && **s == c)
		(*s)++;
	start = *s;
	len = 0;
	while (**s && **s != c)
	{
		(*s)++;
		len++;
	}
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len--)
		word[len] = start[len];
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = get_next_word(&s, c);
		if (!result[i])
		{
			while (i > 0)
				free(result[--i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*str;

	size = ft_strlen(s);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s, size);
	str[size] = '\0';
	return (str);
}
