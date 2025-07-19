/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:34:30 by anpollan          #+#    #+#             */
/*   Updated: 2025/04/24 12:16:02 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	map = ft_lstnew(f(lst->content));
	if (!map)
		return (NULL);
	temp = map;
	while (lst)
	{
		if (lst->next)
			temp->next = ft_lstnew(f(lst->next->content));
		else
			temp->next = NULL;
		if (!temp)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	return (map);
}
