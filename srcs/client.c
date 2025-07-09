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
static	s_sigaction	*initialize_sigaction(void);
void	signal_handler(int signal, siginfo_t *sender_info, void *context);

// int	sender;

int	main(int argc, char *argv[])
{
	int		server_pid;
	int		strlen;
	char	*strlen_str;
	int		i;
	struct sigaction	*sa;

	if (argc != 3)
		return (1);
	sa = initialize_sigaction();
	server_pid = ft_atoi(argv[1]);
	strlen = ft_strlen(argv[2]);
	if (strlen == 0)
		//free memory
		return (1);
	strlen_str = ft_itoa(strlen);
	if (!strlen_str)
		//free memory
		return (1);
	i = 0;
	while (strlen_str[i])
		send_char_as_bits(strlen_str[i++], server_pid);
	send_char_as_bits('!', server_pid);
	free(strlen_str);
	while (*argv[2])
	{
		send_char_as_bits(*argv[2], server_pid);
		argv[2]++;
		// pause();
	}
	send_char_as_bits(*argv[2], server_pid);
	free(sa);
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
		pause();
		usleep(1000);
	}
}

static s_sigaction	*initialize_sigaction(void)
{
	s_sigaction	*sa;

	sa = (s_sigaction *)ft_calloc(1, sizeof(s_sigaction));
	if (!sa)
		return (NULL);
	// sa->sa_handler = &handle_sigusrs;
	sa->sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
	// sigaddset(&(sa->sa_mask), SIGINT);

	return (sa);
}

void	signal_handler(int signal, siginfo_t *sender_info, void *context)
{
	(void)context;
	(void)sender_info;
	(void)signal;
}
