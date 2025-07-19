/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:09 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/19 16:28:26 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

static void	process_sigusr(int signal, siginfo_t *info);
static void	signal_handler(int signal, siginfo_t *info, void *context);
static char	*get_string_length(int signal, bool *got_msglen);
static void	receive_msg(int signal, char **msglen, bool *got_msglen);

static t_server_data	g_server_data;

int	main(void)
{
	t_sa	sa;
	int		pid;

	pid = getpid();
	ft_printf("Server pid: %d\n\n", pid);
	sa = initialize_sigaction(signal_handler);
	while (!g_server_data.sigint_received)
		pause();
	(void)sa;
	return (0);
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	if (signal == SIGINT)
		g_server_data.sigint_received = true;
	else if (signal == SIGUSR1 || signal == SIGUSR2)
		process_sigusr(signal, info);
	(void)context;
}

char	*get_string_length(int signal, bool *got_msglen)
{
	static char		*msglen;
	static int		i;
	unsigned char	*c;
	char			*ret_str;

	if (!msglen)
		msglen = (char *)ft_calloc(1, 11);
	if (!msglen)
		error_exit(g_server_data.current_client);
	c = parse_input_bits(signal);
	if (!c)
		return (NULL);
	msglen[i] = *c;
	if (msglen[i++] == '\0')
	{
		i = 0;
		*got_msglen = true;
		ret_str = msglen;
		msglen = NULL;
		return (ret_str);
	}
	return (NULL);
}

void	receive_msg(int signal, char **msglen, bool *got_msglen)
{
	static char		*msg;
	static int		i;
	int				msglen_int;
	unsigned char	*c;

	if (!msg)
	{
		msglen_int = ft_atoi(*msglen);
		free(*msglen);
		*msglen = NULL;
		msg = (char *)malloc(msglen_int + 1);
		if (!msg)
			error_exit(g_server_data.current_client);
	}
	c = parse_input_bits(signal);
	if (!c)
		return ;
	msg[i] = *c;
	if (msg[i++] == '\0')
		print_msg_and_init(&msg, g_server_data.current_client, got_msglen, &i);
}

void	process_sigusr(int signal, siginfo_t *info)
{
	pid_t			client;
	static char		*msglen;
	static bool		got_msglen;

	client = info->si_pid;
	if (g_server_data.current_client == 0)
		g_server_data.current_client = client;
	if (client != g_server_data.current_client)
	{
		kill(client, SIGUSR2);
		return ;
	}
	if (!got_msglen)
		msglen = get_string_length(signal, &got_msglen);
	else if (got_msglen)
	{
		receive_msg(signal, &msglen, &got_msglen);
		if (!got_msglen)
		{
			kill(client, SIGUSR2);
			g_server_data.current_client = 0;
			return ;
		}
	}
	kill(g_server_data.current_client, SIGUSR1);
}
