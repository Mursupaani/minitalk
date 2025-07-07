/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:37:18 by anpollan          #+#    #+#             */
/*   Updated: 2025/04/22 15:37:19 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static int			check_set(char const c1, char const *set);
static const char	*find_trim_start(char const *s1, char const *set);
static size_t		find_trim_len(char const *s1, char const *set, size_t len);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret_str;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	s1 = find_trim_start(s1, set);
	len = ft_strlen(s1);
	len = find_trim_len(s1, set, len);
	ret_str = (char *)malloc(sizeof(char) * len + 1);
	if (!ret_str)
		return (NULL);
	ft_strlcpy(ret_str, s1, (len + 1));
	return (ret_str);
}

static const char	*find_trim_start(char const *s1, char const *set)
{
	while (s1)
	{
		if (check_set(*s1, set))
			s1++;
		else
			break ;
	}
	return (s1);
}

static size_t	find_trim_len(char const *s1, char const *set, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (check_set(*(s1 + len - 1), set))
			len--;
		else
			break ;
		i++;
	}
	return (len);
}

static int	check_set(char const c1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c1 == set[i])
			return (1);
		i++;
	}
	return (0);
}
