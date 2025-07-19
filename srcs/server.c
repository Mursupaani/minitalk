/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:09 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/19 15:49:51 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

void			process_sigusr(int signal, siginfo_t *info);
char			*get_string_length(int signal, pid_t client, bool *got_msglen);
void			signal_handler(int signal, siginfo_t *info, void *context);
unsigned char	*parse_input_bits(int signal);

static volatile sig_atomic_t	g_sigint_received;

int	main(void)
{
	t_sa	sa;
	int	pid;

	pid = getpid();
	ft_printf("%d\n", pid);
	sa = initialize_server_sigaction(signal_handler);
	while (!g_sigint_received)
		pause();
	(void)sa;
	return (0);
}

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

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	if (signal == SIGINT)
		g_sigint_received = true;
	else if (signal == SIGUSR1 || signal == SIGUSR2)
		process_sigusr(signal, info);
	(void)context;
}

char	*get_string_length(int signal, pid_t client, bool *got_msglen)
{
	static char		*msglen;
	static int		i;
	unsigned char	*c;
	char			*ret_str;

	if (!msglen)
		msglen = (char *)ft_calloc(1, 11);
	if (!msglen)
		error_exit(client);
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

void	receive_msg(int signal, pid_t client, char **msglen, bool *got_msglen)
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
			error_exit(client);
	}
	c = parse_input_bits(signal);
	if (!c)
		return ;
	msg[i] = *c;
	if (msg[i++] == '\0')
		print_msg_and_init(&msg, client, got_msglen, &i);
}

