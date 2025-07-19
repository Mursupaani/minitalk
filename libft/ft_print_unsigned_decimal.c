/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_decimal.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:52:00 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 14:49:05 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_uint_digits(unsigned int n);

int	ft_print_unsigned_decimal(va_list args)
{
	char			*num_str;
	unsigned int	num;
	int				end;
	int				bytes_printed;

	num = va_arg(args, unsigned int);
	end = count_uint_digits(num);
	num_str = (char *)malloc(sizeof(char) * (end + 1));
	if (!num_str)
		return (0);
	num_str[end--] = '\0';
	while (end >= 0)
	{
		if (num < 0 && end == 0)
			num_str[end] = '-';
		else
			num_str[end] = num % 10 + '0';
		num /= 10;
		end--;
	}
	ft_putstr_fd(num_str, 1);
	bytes_printed = ft_strlen(num_str);
	free(num_str);
	return (bytes_printed);
}

static int	count_uint_digits(unsigned int n)
{
	int			len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}
