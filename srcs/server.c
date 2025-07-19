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

static void		print_server_pid(void);
void	process_sigusr(int signal, siginfo_t *info);
char			*get_string_length(int signal, pid_t client, bool *got_msg_len);
void			signal_handler(int signal, siginfo_t *info, void *context);
unsigned char	*parse_input_bits(int signal);
void			error_exit(pid_t client);

static volatile sig_atomic_t	g_sigint_received;

int	main(void)
{
	t_sa	sa;

	sa = initialize_server_sigaction(signal_handler);
	print_server_pid();
	while (!g_sigint_received)
		pause();
	(void)sa;
	return (0);
}

void	print_server_pid(void)
{
	int	pid;

	pid = getpid();
	ft_printf("%d\n", pid);
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



void	process_sigusr(int signal, siginfo_t *info)
{
	pid_t			client;
	static char		*msg_len;
	static bool		got_msg_len;
	static pid_t	current_client;

		client = info->si_pid;
		if (current_client == 0)
			current_client = client;
		if (client != current_client)
		{
			kill(client, SIGUSR2);
			return ;
		}
		if (!got_msg_len)
			msg_len = get_string_length(signal, client, &got_msg_len);
		else if (got_msg_len)
		{
			receive_msg(signal, client, &msg_len, &got_msg_len);
			if (!got_msg_len)
			{
				kill(client, SIGUSR2);
				current_client = 0;
				return ;
			}
		}
		kill(client, SIGUSR1);
}

char	*get_string_length(int signal, pid_t client, bool *got_msg_len)
{
	static char		*msg_len;
	static int		i;
	unsigned char	*c;
	char			*ret_str;

	if (!msg_len)
		msg_len = (char *)ft_calloc(1, 11);
	if (!msg_len)
		error_exit(client);
	c = parse_input_bits(signal);
	if (!c)
		return (NULL);
	msg_len[i] = *c;
	if (msg_len[i++] == '\0')
	{
		i = 0;
		*got_msg_len = true;
		ret_str = msg_len;
		msg_len = NULL;
		return (ret_str);
	}
	return (NULL);
}

void	receive_msg(int signal, pid_t client, char **msg_len, bool *got_msg_len)
{
	static char		*msg;
	static int		i;
	int				msg_len_int;
	unsigned char	*c;

	if (!msg)
	{
		msg_len_int = ft_atoi(*msg_len);
		free(*msg_len);
		*msg_len = NULL;
		msg = (char *)malloc(msg_len_int + 1);
		if (!msg)
			error_exit(client);
	}
	c = parse_input_bits(signal);
	if (!c)
		return ;
	msg[i] = *c;
	if (msg[i++] == '\0')
		print_msg_and_init(&msg, client, got_msg_len, &i);
}

void	error_exit(pid_t client)
{
	kill(client, SIGUSR2);
	exit(EXIT_FAILURE);
}

void	print_msg_and_init(char **msg, pid_t client, bool *got_msg_len, int *i)
{
	ft_printf("%d: %s\n",client, *msg);
	free(*msg);
	*msg = NULL;
	*i = 0;
	*got_msg_len = false;
}
