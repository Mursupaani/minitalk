/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:32:17 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 14:48:56 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_decimal(va_list args)
{
	int		num;
	char	*num_str;
	int		bytes_printed;

	num = va_arg(args, int);
	num_str = ft_itoa(num);
	ft_putstr_fd(num_str, 1);
	bytes_printed = ft_strlen(num_str);
	free(num_str);
	return (bytes_printed);
}
