/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 22:58:43 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/24 11:49:07 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_malset(int size, char set)
{
	char *trg;

	trg = 0;
	if (size > 0)
	{
		trg = ft_memalloc(size + 1);
		ft_memset(trg, set, size);
	}
	return (trg);
}
