/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:24:53 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/19 16:25:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

unsigned char	*parse_input_bits(int signal)
{
	static int				counter;
	static unsigned char	c[1];

	if (counter == 0)
		*c = 0;
	if (signal == SIGUSR1)
	{
		*c = *c << 1;
		*c += 1;
		counter++;
	}
	else if (signal == SIGUSR2)
	{
		*c = *c << 1;
		counter++;
	}
	if (counter < 8)
		return (NULL);
	else
	{
		counter = 0;
		return (c);
	}
}
