/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:33:00 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 14:48:47 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string(va_list args)
{
	char	*str;
	int		bytes_printed;

	str = va_arg(args, char *);
	if (str == NULL)
		return (write(1, "(null)", 6));
	bytes_printed = 0;
	while (*str)
	{
		write(1, str, 1);
		bytes_printed++;
		str++;
	}
	return (bytes_printed);
}
