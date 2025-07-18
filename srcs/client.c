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

s_sigaction	initialize_sigaction(void (*handler)(int, siginfo_t *, void *));
void		send_message(const char *message, pid_t pid, s_sigaction sa);
void		signal_handler(int signal, siginfo_t *info, void *context);
void		signal_handler2(int signal, siginfo_t *info, void *context);

static volatile sig_atomic_t g_signal_received;

int	main(int argc, char *argv[])
{
	pid_t		server_pid;
	s_sigaction	sa;

	if (argc != 3 || argv[2][0] == '\0')
		return (EXIT_FAILURE);
	server_pid = ft_atoi(argv[1]);
	if (server_pid == 0)
		return (EXIT_FAILURE);
	sa = initialize_sigaction(&signal_handler);
	send_message(argv[2], server_pid, sa);
	return (0);
}


s_sigaction	initialize_sigaction(void (*handler)(int, siginfo_t *, void *))
{
	s_sigaction	sa;

	// sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	// sa.sa_flags = SA_RESTART;

	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// sigaddset(&(sa->sa_mask), SIGINT);
	return (sa);
}

void	send_message(const char *message, pid_t pid, s_sigaction sa)
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
	while (*message)
		send_char_as_bits(*message++, pid);
	sa = initialize_sigaction(&signal_handler2);
	send_char_as_bits(*message, pid);
	free(strlen_str);
	(void)sa;
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGUSR1)
		g_signal_received = 1;
	if (signal == SIGUSR2)
	{
		ft_printf("Server is busy. Please try again in a moment.\n");
		exit(EXIT_FAILURE);
	}
}

void	signal_handler2(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGUSR1)
		g_signal_received = 1;
	if (signal == SIGUSR2)
	{
		ft_printf("Message sent.\n");
		exit(EXIT_SUCCESS);
	}
}

void	send_char_as_bits(unsigned char c, int pid)
{
	unsigned char	current_bit;
	int				i;
	int				current_signal;

	current_bit = 0;
	i = 8;
	while (i--)
	{
		g_signal_received = 0;
		current_bit = c & 0b10000000;
		if (current_bit)
			current_signal = SIGUSR1;
		else
			current_signal = SIGUSR2;
		kill(pid, current_signal);
		while (!g_signal_received)
			usleep(50);
		usleep(50);
		c = c << 1;
	}
}

