/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:32:21 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/07 12:35:26 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

void	send_char_as_bits(unsigned char c, int server_pid);

int	main(int argc, char *argv[])
{
	int	server_pid;

	if (argc != 3)
		return (1);
	server_pid = ft_atoi(argv[1]);
	ft_printf("Server pid: %d\n", server_pid);
	ft_printf("Message: %s\n", argv[2]);
	while (*argv[2])
	{
		send_char_as_bits(*argv[2], server_pid);
		argv[2]++;
	}
	send_char_as_bits(*argv[2], server_pid);
	return (0);
}

void	send_char_as_bits(unsigned char c, int server_pid)
{
	unsigned char	current_bit;
	int				i;

	current_bit = 0;
	i = 8;
	while (i--)
	{
		current_bit = c & 10000000;
		if (current_bit)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		c = c << 1;
		usleep(1);
	}
}
