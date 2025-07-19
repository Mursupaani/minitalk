/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:32:35 by anpollan          #+#    #+#             */
/*   Updated: 2025/04/22 15:32:37 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The values returned are nonzero if the character c falls into the
// tested class, and zero if not.
int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
