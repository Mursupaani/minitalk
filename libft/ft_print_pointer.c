/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:28:52 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 14:48:52 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_ptr_in_hex(unsigned long num, int *bytes_printed);

int	ft_print_pointer(va_list args)
{
	int				bytes_printed;
	void			*ptr;

	ptr = va_arg(args, void *);
	if (!ptr)
		return (write(1, "(nil)", 5));
	bytes_printed = write(1, "0x", 2);
	ft_print_ptr_in_hex((unsigned long)ptr, &bytes_printed);
	return (bytes_printed);
}

static void	ft_print_ptr_in_hex(unsigned long num, int *bytes_printed)
{
	char	*base;
	char	hex;

	base = "0123456789abcdef";
	if (num >= 16)
		ft_print_ptr_in_hex(num / 16, bytes_printed);
	hex = base[num % 16];
	write(1, &hex, 1);
	*bytes_printed = *bytes_printed + 1;
}
