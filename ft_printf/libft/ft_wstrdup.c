/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 14:27:22 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/23 14:27:30 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t	*ft_wstrdup(const char *str)
{
	int		i;
	wchar_t	*new;

	i = ft_strlen(str);
	new = ft_memalloc(sizeof(wchar_t) * i + 1);
	if (!i)
		return (0);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}
