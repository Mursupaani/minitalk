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
unsigned char		*parse_input_bits(int signal, pid_t client);

static pid_t	g_current_client = -1;

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
		// write(1, &c, 1);
		// usleep(200);
		kill(client, SIGUSR1);
		return (c);
	}
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	pid_t			client;
	static char		*strlen_str;
	static int		i;
	static bool		writing_string;
	static char		*message;
	unsigned char	*c;
	int				strlen;

	client = info->si_pid;
	if (g_current_client == -1)
		g_current_client = client;
	if (client != g_current_client)
	{
		kill(client, SIGUSR2);
		return ;
	}
	if (!writing_string)
	{
		if (!strlen_str)
			strlen_str = (char *)ft_calloc(1, 11);
		if (!strlen_str)
			// FIXME: What else needs to be done?
			return ;
		c = parse_input_bits(signal, client);
		if (!c)
			return ;
		strlen_str[i] = *c;
		if (strlen_str[i++] == '\0')
		{
			writing_string = true;
			i = 0;
		}
		// write(1, c, 1);
	}
	else if (writing_string)
	{
		if (!message)
		{
			strlen = ft_atoi(strlen_str);
			free(strlen_str);
			strlen_str = NULL;
			message = (char *)malloc(strlen + 1);
			if (!message)
				// FIXME: What else needs to be done?
				return ;
		// ft_printf("strlen: %d\n", strlen);
		}
		c = parse_input_bits(signal, client);
		if (!c)
			return ;
		// ft_printf("c: %d\n", *c);
		message[i] = *c;
		if (message[i++] == '\0')
		{
			ft_printf("%s", message);
			free(message);
			message = NULL;
			writing_string = false;
			i = 0;
			g_current_client = -1;
		}
	}

	(void)context;
	// char	current_signal;
	// if (signal == SIGUSR1)
	// 	current_signal = '1';
	// else if (signal == SIGUSR2)
	// 	current_signal = '0';
	// write(1, &current_signal, 1);
}
