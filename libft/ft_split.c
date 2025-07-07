/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:35:51 by anpollan          #+#    #+#             */
/*   Updated: 2025/04/22 15:35:52 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c);
static size_t	sub_strlen(char *s, char c);
static char		*find_substr_start(char *s, char c);
static char		**free_array(char **array, size_t array_size);

char	**ft_split(char const *s, char c)
{
	char	**array;
	char	*temp;
	size_t	words;
	size_t	i;
	size_t	sub_len;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	temp = (char *)s;
	i = 0;
	while (i < words)
	{
		temp = find_substr_start(temp, c);
		sub_len = sub_strlen(temp, c);
		array[i] = ft_substr(temp, 0, sub_len);
		if (!array[i++])
			return (free_array(array, words + 1));
		temp += sub_len;
	}
	array[i] = NULL;
	return (array);
}

static size_t	count_words(const char *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			counter++;
		while (*s && *s != c)
			s++;
	}
	return (counter);
}

static size_t	sub_strlen(char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

static char	*find_substr_start(char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

static char	**free_array(char **array, size_t array_size)
{
	size_t	i;

	i = 0;
	while (i < array_size)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	return (NULL);
}
