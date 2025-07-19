/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:22:19 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 14:49:23 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_flag(int c);
static int	choose_conversion(int conversion, va_list args);

// Upon successful return, ft_printf function returns the number of bytes
// printed (excluding the null byte used to end output to strings).
int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		bytes_printed;
	int		conversion_type;

	va_start(args, format);
	bytes_printed = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			conversion_type = check_flag(format[i + 1]);
			if (conversion_type != ERR)
				bytes_printed += choose_conversion(conversion_type, args);
			else
				bytes_printed += ft_print_percentage();
			i++;
		}
		else
			bytes_printed += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (bytes_printed);
}

static int	check_flag(int c)
{
	if (c == 'c')
		return (CHAR);
	else if (c == 's')
		return (STR);
	else if (c == 'p')
		return (PTR);
	else if (c == 'd')
		return (DEC);
	else if (c == 'i')
		return (INT);
	else if (c == 'u')
		return (UINT);
	else if (c == 'x')
		return (L_HEX);
	else if (c == 'X')
		return (U_HEX);
	else if (c == '%')
		return (PERC);
	else
		return (ERR);
}

static int	choose_conversion(int conversion, va_list args)
{
	int	bytes_printed;

	bytes_printed = 0;
	if (conversion == CHAR)
		bytes_printed = ft_print_char(args);
	else if (conversion == STR)
		bytes_printed = ft_print_string(args);
	else if (conversion == PTR)
		bytes_printed = ft_print_pointer(args);
	else if (conversion == DEC)
		bytes_printed = ft_print_decimal(args);
	else if (conversion == INT)
		bytes_printed = ft_print_integer(args);
	else if (conversion == UINT)
		bytes_printed = ft_print_unsigned_decimal(args);
	else if (conversion == L_HEX)
		bytes_printed = ft_print_lowercase_hex(args);
	else if (conversion == U_HEX)
		bytes_printed = ft_print_uppercase_hex(args);
	else if (conversion == PERC)
		bytes_printed = ft_print_percentage();
	return (bytes_printed);
}
