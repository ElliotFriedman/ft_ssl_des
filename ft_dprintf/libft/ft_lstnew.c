/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 15:30:24 by efriedma          #+#    #+#             */
/*   Updated: 2018/03/06 23:01:38 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lst;

	if ((lst = ft_memalloc(sizeof(t_list))) && content)
	{
		if ((lst->content = malloc(content_size)))
		{
			ft_memcpy(lst->content, content, content_size);
			lst->content_size = content_size;
		}
		else
			ft_memdel((void **)&lst);
	}
	return (lst);
}
