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

static void				print_server_pid(void);
static struct sigaction	*initialize_sigaction(void);
void					signal_handler(int signal, siginfo_t *info, void *null);
void					handle_sigusrs(int signal);
char					parse_input_bits(int signal);
char					read_client_signals(struct sigaction *sa);

unsigned char	c;

int	main(void)
{
	struct sigaction	*sa;
	siginfo_t			sender;

	sa = initialize_sigaction();
	if (!sa)
		return (1);
	print_server_pid();
	while (1)
	{
		pause();
		read_client_signals(sa);

	}
	free(sa);
	return (0);
}

static void	print_server_pid(void)
{
	int	pid;

	pid = getpid();
	ft_printf("%d\n", pid);
}

static struct sigaction	*initialize_sigaction(void)
{
	struct sigaction	*sa;

	sa = (struct sigaction *)ft_calloc(1, sizeof(struct sigaction));
	if (!sa)
		return (NULL);
	// sa->sa_handler = &handle_sigusrs;
	sa->sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
	// sigaddset(&(sa->sa_mask), SIGINT);

	return (sa);
}

void	handle_sigusrs(int signal)
{
	parse_input_bits(signal);
}

char	parse_input_bits(int signal)
{
	static int				counter;

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
		return (c);
	}
}

void	signal_handler(int signal, siginfo_t *info, void *null)
{
	(void)null;
}
