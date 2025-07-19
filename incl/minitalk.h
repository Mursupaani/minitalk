/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:47 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/19 16:27:45 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include "../libft/libft.h"

typedef struct sigaction	t_sa;

typedef struct s_server_data
{
	pid_t					current_client;
	volatile sig_atomic_t	sigint_received;
}	t_server_data;

typedef struct s_client_data
{
	char					*msglen;
	volatile sig_atomic_t	signal_received;
}	t_client_data;

t_sa			initialize_sigaction(void (*handler)(int, siginfo_t *, void *));
int				*ft_atoi_safe(const char *nptr);
void			print_msg_and_init(char **msg, pid_t client,
					bool *got_length, int *i);
void			error_exit(pid_t client);
void			print_msg_and_init(char **msg, pid_t client,
					bool *got_msglen, int *i);
unsigned char	*parse_input_bits(int signal);

#endif
