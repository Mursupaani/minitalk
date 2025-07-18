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

void			print_server_pid(void);
s_sigaction		initialize_sigaction(void);
char			*get_string_length(int signal, pid_t client, bool *got_length);
void			receive_message(int signal, pid_t client, char **msg_len, bool *got_length);
void			signal_handler(int signal, siginfo_t *info, void *context);
unsigned char	*parse_input_bits(int signal);
void			error_exit(pid_t client);
void			print_message_and_initialize(char **message, bool *got_length, int *i);


int	main(void)
{
	s_sigaction	sa;

	sa = initialize_sigaction();
	print_server_pid();
	while (1)
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

s_sigaction	initialize_sigaction(void)
{
	s_sigaction	sa;

	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = SA_SIGINFO;

	sa.sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// sigfillset(&sa.sa_mask);
	// sigaddset(&(sa->sa_mask), SIGINT);

	return (sa);
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
	pid_t			client;
	static char		*msg_len;
	static bool		got_length;
	static pid_t	current_client;

	(void)context;
	client = info->si_pid;
	if (current_client == 0)
		current_client = client;
	if (client != current_client)
	{
		kill(client, SIGUSR2);
		return ;
	}
	if (!got_length)
		msg_len = get_string_length(signal, client, &got_length);
	else if (got_length)
	{
		receive_message(signal, client, &msg_len, &got_length);
		if (!got_length)
		{
			kill(client, SIGUSR2);
			current_client = 0;
			return ;
		}
	}
	kill(client, SIGUSR1);
}

char	*get_string_length(int signal, pid_t client, bool *got_length)
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
		*got_length = true;
		ret_str = msg_len;
		msg_len = NULL;
		return (ret_str);
	}
	return (NULL);
}

void	receive_message(int signal, pid_t client, char **msg_len, bool *got_length)
{
	static char		*message;
	static int		i;
	int				msg_len_int;
	unsigned char	*c;

	if (!message)
	{
		msg_len_int = ft_atoi(*msg_len);
		free(*msg_len);
		*msg_len = NULL;
		message = (char *)malloc(msg_len_int + 1);
		if (!message)
			error_exit(client);
	}
	c = parse_input_bits(signal);
	if (!c)
		return ;
	message[i] = *c;
	if (message[i++] == '\0')
		print_message_and_initialize(&message, got_length, &i);
}

void	error_exit(pid_t client)
{
	kill(client, SIGUSR2);
	exit(EXIT_FAILURE);
}

void	print_message_and_initialize(char **message, bool *got_length, int *i)
{
	ft_printf("%s\n", *message);
	free(*message);
	*message = NULL;
	*i = 0;
	*got_length = false;
}
