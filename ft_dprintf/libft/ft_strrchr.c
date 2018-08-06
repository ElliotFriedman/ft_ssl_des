/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:09:34 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/24 17:11:08 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s1, int c)
{
	int		i;
	int		ctr;

	i = -1;
	ctr = -1;
	while (s1[++i])
		if (s1[i] == (const char)c)
			ctr = i;
	if (c == 0)
		ctr = i;
	if (ctr > -1)
		return ((char*)s1 + ctr);
	else
		return ((char*)0);
}
