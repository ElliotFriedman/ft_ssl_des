/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 22:47:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/03 22:51:04 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t len)
{
	char	*cpy;
	int		a;
	int		i;

	a = (int)ft_strlen(str);
	cpy = (char*)ft_memalloc(sizeof(char) * a + 1);
	i = 0;
	if (cpy)
		ft_strncpy(cpy, str, len);
	return (cpy);
}
