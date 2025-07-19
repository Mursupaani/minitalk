/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_in_hex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:04:53 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 14:29:04 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_num_in_hex(unsigned int num, int *bytes_printed, int conv)
{
	char	*base;
	char	hex;

	base = "0123456789abcdef";
	if (num >= 16)
		ft_print_num_in_hex(num / 16, bytes_printed, conv);
	hex = base[num % 16];
	if (conv == U_HEX)
		hex = ft_toupper(hex);
	write(1, &hex, 1);
	*bytes_printed = *bytes_printed + 1;
}
