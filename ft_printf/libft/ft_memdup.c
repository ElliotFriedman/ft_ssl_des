/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:45:28 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/08 22:19:40 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	*ft_memdup(unsigned long long *stack, size_t bytes)
{
	unsigned long long	*ret;
	size_t				i;

	i = 0;
	ret = ft_memalloc(bytes + 8);
	bytes /= 8;
	while (i < bytes)
	{
		ret[i] = stack[i];
		i++;
	}
	return (ret);
}
