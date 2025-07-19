/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:52:59 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/09 18:57:36 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

s_sa	initialize_server_sigaction(void (*handler)(int, siginfo_t *, void *))
{
	s_sa	sa;


	// WARN: How do these work?
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);

	return (sa);
}

s_sa	initialize_client_sigaction(void (*handler)(int, siginfo_t *, void *))
{
	s_sa	sa;

	sa.sa_flags = SA_SIGINFO;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	return (sa);
}
