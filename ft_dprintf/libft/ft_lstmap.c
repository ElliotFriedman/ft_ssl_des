/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:27:21 by efriedma          #+#    #+#             */
/*   Updated: 2018/03/06 22:29:34 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *buff;

	if (!lst || !f)
		return (lst);
	new = f(lst);
	buff = new;
	while (lst->next != 0)
	{
		lst = lst->next;
		buff->next = f(lst);
		buff = buff->next;
	}
	return (new);
}
