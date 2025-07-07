/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:35:39 by anpollan          #+#    #+#             */
/*   Updated: 2025/04/22 15:35:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	num;
	char		c;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	if (num > 9)
	{
		ft_putnbr_fd(num / 10, fd);
		num %= 10;
	}
	if (num < 10)
	{
		c = num + '0';
		write(fd, &c, 1);
	}
}
