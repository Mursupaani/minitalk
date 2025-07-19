/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:32:21 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/19 15:48:04 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

static void	send_message(const char *message, pid_t pid, t_sa sa);
static void	signal_handler_start(int signal, siginfo_t *info, void *context);
static void	signal_handler_end(int signal, siginfo_t *info, void *context);
static void	send_char_as_bits(unsigned char c, int pid);

static t_client_data	g_client_data;

int	main(int argc, char *argv[])
{
	int		*temp_server_pid;
	pid_t	server_pid;
	t_sa	sa;

	if (argc != 3 || argv[2][0] == '\0')
		return (EXIT_FAILURE);
	temp_server_pid = ft_atoi_safe(argv[1]);
	if (!temp_server_pid)
		return (EXIT_FAILURE);
	server_pid = *temp_server_pid;
	if (server_pid < 0)
		return (EXIT_FAILURE);
	sa = initialize_client_sigaction(&signal_handler_start);
	send_message(argv[2], server_pid, sa);
	return (0);
}

static void	send_message(const char *message, pid_t pid, t_sa sa)
{
	int		strlen;
	int		i;

	strlen = ft_strlen(message);
	if (strlen == 0)
		exit(EXIT_FAILURE);
	g_client_data.msglen = ft_itoa(strlen);
	if (!g_client_data.msglen)
		exit(EXIT_FAILURE);
	i = 0;
	while (g_client_data.msglen[i])
		send_char_as_bits(g_client_data.msglen[i++], pid);
	send_char_as_bits(g_client_data.msglen[i], pid);
	free(g_client_data.msglen);
	g_client_data.msglen = NULL;
	while (*message)
		send_char_as_bits(*message++, pid);
	sa = initialize_client_sigaction(&signal_handler_end);
	send_char_as_bits(*message, pid);
	(void)sa;
}

static void	signal_handler_start(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGUSR1)
		g_client_data.signal_received = 1;
	if (signal == SIGUSR2)
	{
		ft_printf("Server is busy. Please try again in a moment.\n");
		exit(EXIT_FAILURE);
	}
	if (signal == SIGINT)
	{
		if (g_client_data.msglen)
			free(g_client_data.msglen);
		exit(EXIT_SUCCESS);
	}
}

static void	signal_handler_end(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGUSR1)
		g_client_data.signal_received = 1;
	if (signal == SIGUSR2)
	{
		ft_printf("Message sent.\n");
		exit(EXIT_SUCCESS);
	}
	if (signal == SIGINT)
	{
		if (g_client_data.msglen)
			free(g_client_data.msglen);
		exit(EXIT_SUCCESS);
	}
}

static void	send_char_as_bits(unsigned char c, int pid)
{
	unsigned char	current_bit;
	int				i;
	int				current_signal;

	current_bit = 0;
	i = 8;
	while (i--)
	{
		g_client_data.signal_received = 0;
		current_bit = c & 0b10000000;
		if (current_bit)
			current_signal = SIGUSR1;
		else
			current_signal = SIGUSR2;
		kill(pid, current_signal);
		while (!g_client_data.signal_received)
			usleep(50);
		usleep(50);
		c = c << 1;
	}
}

