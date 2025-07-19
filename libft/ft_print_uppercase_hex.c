/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uppercase_hex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:58:40 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 14:49:14 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uppercase_hex(va_list args)
{
	int				bytes_printed;
	unsigned int	num;

	num = va_arg(args, unsigned int);
	bytes_printed = 0;
	ft_print_num_in_hex(num, &bytes_printed, U_HEX);
	return (bytes_printed);
}
