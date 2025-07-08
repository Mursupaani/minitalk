/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:09 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/07 12:00:37 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

static void			print_server_pid(void);
static s_sigaction	*initialize_sigaction(void);
void				signal_handler(int signal, siginfo_t *info, void *context);
char				parse_input_bits(int signal, pid_t sender);

char	c;

int	main(void)
{
	s_sigaction	*sa;

	sa = initialize_sigaction();
	if (!sa)
		return (1);
	print_server_pid();
	while (1)
		pause();
	free(sa);
	return (0);
}

static void	print_server_pid(void)
{
	int	pid;

	pid = getpid();
	ft_printf("%d\n", pid);
}

static	s_sigaction	*initialize_sigaction(void)
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

char	parse_input_bits(int signal, pid_t sender)
{
	static int	counter;

	if (counter >= 8)
		c = 0;
	if (signal == SIGUSR1)
	{
		c = c << 1;
		c += 1;
		counter++;
	}
	else if (signal == SIGUSR2)
	{
		c = c << 1;
		counter++;
	}
	if (counter < 8)
		return (0);
	else
	{
		counter = 0;
		write(1, &c, 1);
		usleep(200);
		kill(sender, SIGUSR1);
		return (c);
	}
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	pid_t	sender;
	// char	current_signal;

	(void)context;
	// if (signal == SIGUSR1)
	// 	current_signal = '1';
	// else if (signal == SIGUSR2)
	// 	current_signal = '0';
	// write(1, &current_signal, 1);
	sender = info->si_pid;
	parse_input_bits(signal, sender);
}
