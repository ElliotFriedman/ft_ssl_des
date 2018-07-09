/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_umalset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 12:44:59 by efriedma          #+#    #+#             */
/*   Updated: 2018/06/02 12:47:32 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	*ft_umalset(int size, unsigned char set)
{
	unsigned char *trg;

	trg = 0;
	if (size > 0)
	{
		trg = ft_memalloc(size + 1);
		ft_memset(trg, set, size);
	}
	return (trg);
}
