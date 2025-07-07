/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:32:19 by anpollan          #+#    #+#             */
/*   Updated: 2025/04/22 15:32:20 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	check_overflow;
	size_t	i;

	if (nmemb == 0 || size == 0)
	{
		ptr = (void *)malloc(1);
		return (ptr);
	}
	check_overflow = nmemb * size;
	if (check_overflow / nmemb != size)
	{
		return (NULL);
	}
	ptr = (void *)malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < (size * nmemb))
		((char *)ptr)[i++] = 0;
	return (ptr);
}
