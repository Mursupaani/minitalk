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

// WARN: How do these work?
t_sa	initialize_server_sigaction(void (*handler)(int, siginfo_t *, void *))
{
	t_sa	sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	return (sa);
}

t_sa	initialize_client_sigaction(void (*handler)(int, siginfo_t *, void *))
{
	t_sa	sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	return (sa);
}

int	*ft_atoi_safe(const char *nptr)
{
	static long int	result[1];
	int				sign;

	sign = 1;
	*result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
		if (!ft_isdigit(*nptr))
			return (NULL);
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		*result *= 10;
		*result += *nptr - '0';
		nptr++;
	}
	*result *= sign;
	if (*result > INT_MAX || *result < INT_MIN || *nptr != '\0')
		return (NULL);
	return ((int *)result);
}
