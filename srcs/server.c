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
static s_sigaction	initialize_sigaction(void);
char				*get_string_length(int signal, pid_t client, bool *receiving_message);
void	get_message_and_print(int signal, pid_t client, char **strlen_str, bool *receiving_message);
void				signal_handler(int signal, siginfo_t *info, void *context);
unsigned char		*parse_input_bits(int signal, pid_t client);

static pid_t	g_current_client = -1;

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

static void	print_server_pid(void)
{
	int	pid;

	pid = getpid();
	ft_printf("%d\n", pid);
}

static	s_sigaction	initialize_sigaction(void)
{
	s_sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	// sigaddset(&(sa->sa_mask), SIGINT);

	return (sa);
}

unsigned char	*parse_input_bits(int signal, pid_t client)
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
	{
		kill(client, SIGUSR1);
		return (NULL);
	}
	else
	{
		counter = 0;
		kill(client, SIGUSR1);
		return (c);
	}
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	pid_t			client;
	char			*strlen_str;
	static bool		receiving_message;

	client = info->si_pid;
	if (g_current_client == -1)
		g_current_client = client;
	if (client != g_current_client)
	{
		kill(client, SIGUSR2);
		return ;
	}
	if (!receiving_message)
		strlen_str = get_string_length(signal, client, &receiving_message);
	else if (receiving_message)
		get_message_and_print(signal, client, &strlen_str, &receiving_message);

	(void)context;
}

char	*get_string_length(int signal, pid_t client, bool *receiving_message)
{
	static char		*strlen_str;
	static int		i;
	unsigned char	*c;
	char			*ret_str;

	if (!strlen_str)
		strlen_str = (char *)ft_calloc(1, 11);
	if (!strlen_str)
		exit(EXIT_FAILURE);
	c = parse_input_bits(signal, client);
	if (!c)
		return (NULL);
	strlen_str[i] = *c;
	if (strlen_str[i++] == '\0')
	{
		i = 0;
		*receiving_message = true;
		ret_str = strlen_str;
		strlen_str = NULL;
		return (ret_str);
	}
	return (NULL);
}

void	get_message_and_print(int signal, pid_t client, char **strlen_str, bool *receiving_message)
{
	static char		*message;
	static int		i;
	int				strlen;
	unsigned char	*c;

	if (!message)
		{
			strlen = ft_atoi(*strlen_str);
			free(*strlen_str);
			*strlen_str = NULL;
			message = (char *)malloc(strlen + 1);
			if (!message)
				//FIXME: notify client
				exit(EXIT_FAILURE);
		}
		c = parse_input_bits(signal, client);
		if (!c)
			return ;
		message[i] = *c;
		write(1, c, 1);
		if (message[i++] == '\0')
		{
			ft_printf("%s\n", message);
			free(message);
			message = NULL;
			i = 0;
			g_current_client = -1;
			*receiving_message = false;
		}
}
