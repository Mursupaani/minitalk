/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:47 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/07 12:04:56 by anpollan         ###   ########.fr       */
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

typedef struct s_client_data
{
	char					*msg_len;
	volatile sig_atomic_t	signal_received;
}	t_client_data;

t_sa	initialize_client_sigaction(void (*handler)(int, siginfo_t *, void *));
t_sa	initialize_server_sigaction(void (*handler)(int, siginfo_t *, void *));
int		*ft_atoi_safe(const char *nptr);
void	receive_msg(int signal, pid_t client, char **msg_len, bool *got_length);
void	print_msg_and_init(char **msg, pid_t client, bool *got_length, int *i);

#endif
