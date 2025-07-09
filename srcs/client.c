/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:32:21 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/09 18:58:06 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

static s_sigaction	initialize_sigaction(void);
static void			send_message(const char *message, pid_t pid);
static void			signal_handler(int signal, siginfo_t *info, void *context);

static volatile sig_atomic_t g_signal_received;

int	main(int argc, char *argv[])
{
	pid_t		server_pid;
	s_sigaction	sa;

	if (argc != 3)
		return (EXIT_FAILURE);
	server_pid = ft_atoi(argv[1]);
	sa = initialize_sigaction();
	send_message(argv[2], server_pid);
	//FIXME:Handle this better
	(void)sa;
	return (0);
}


static s_sigaction	initialize_sigaction(void)
{
	s_sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	// sa.sa_flags = SA_RESTART;

	sa.sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// sigaddset(&(sa->sa_mask), SIGINT);
	return (sa);
}

static void	send_message(const char *message, pid_t pid)
{
	int		strlen;
	char	*strlen_str;
	int		i;

	strlen = ft_strlen(message);
	if (strlen == 0)
		exit(EXIT_FAILURE);
	strlen_str = ft_itoa(strlen);
	if (!strlen_str)
		exit(EXIT_FAILURE);
	i = 0;
	while (strlen_str[i])
		send_char_as_bits(strlen_str[i++], pid);
	send_char_as_bits(strlen_str[i], pid);
	free(strlen_str);
	while (*message)
		send_char_as_bits(*message++, pid);
	send_char_as_bits(*message, pid);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGUSR1)
		g_signal_received = 1;
	if (signal == SIGUSR2)
		exit(EXIT_FAILURE);
}

void	send_char_as_bits(unsigned char c, int pid)
{
	unsigned char	current_bit;
	int				i;

	current_bit = 0;
	i = 8;
	while (i--)
	{
		g_signal_received = 0;
		current_bit = c & 0b10000000;
		if (current_bit)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_signal_received)
			usleep(50);
			// pause();
		usleep(50);
		c = c << 1;
	}
}

