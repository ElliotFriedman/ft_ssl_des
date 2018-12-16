/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:23:21 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/08 23:48:06 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;
	int		a;
	int		i;

	a = (int)ft_strlen(str);
	cpy = (char*)ft_memalloc(sizeof(char) * a + 1);
	i = 0;
	if (cpy)
		ft_strcpy(cpy, str);
	return (cpy);
}
