/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:44:15 by anpollan          #+#    #+#             */
/*   Updated: 2025/07/19 15:50:33 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minitalk.h"

void	process_sigusr(int signal, siginfo_t *info)
{
	pid_t			client;
	static char		*msglen;
	static bool		got_msglen;
	static pid_t	current_client;

	client = info->si_pid;
	if (current_client == 0)
		current_client = client;
	if (client != current_client)
	{
		kill(client, SIGUSR2);
		return ;
	}
	if (!got_msglen)
		msglen = get_string_length(signal, client, &got_msglen);
	else if (got_msglen)
	{
		receive_msg(signal, client, &msglen, &got_msglen);
		if (!got_msglen)
		{
			kill(client, SIGUSR2);
			current_client = 0;
			return ;
		}
	}
	kill(client, SIGUSR1);
}

