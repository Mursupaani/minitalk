/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:59 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/09 18:57:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

void	send_char_as_bits(unsigned char c, int pid)
{
	unsigned char	current_bit;
	int				i;

	current_bit = 0;
	i = 8;
	while (i--)
	{
		// usleep(10000);
		current_bit = c & 0b10000000;
		if (current_bit)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		c = c << 1;
	}
}

