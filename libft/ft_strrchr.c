/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:37:08 by anpollan          #+#    #+#             */
/*   Updated: 2025/04/24 17:15:27 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	end;

	end = ft_strlen(s);
	while (end > 0)
	{
		if (s[end] == (unsigned char)c)
			return ((char *)&s[end]);
		end--;
	}
	if (s[end] == (unsigned char)c)
		return ((char *)&s[end]);
	return (NULL);
}
