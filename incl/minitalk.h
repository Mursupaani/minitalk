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
# include "../libft/libft.h"

typedef struct sigaction s_sa;

void	send_char_as_bits(unsigned char c, pid_t pid);
s_sa	initialize_client_sigaction(void (*handler)(int, siginfo_t *, void *));

#endif
