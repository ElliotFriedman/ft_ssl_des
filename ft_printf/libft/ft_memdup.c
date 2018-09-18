/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:45:28 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/17 17:51:58 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/ft_printf.h"

unsigned long long	*ft_memdup(unsigned long long *stack, size_t bytes)
{
	unsigned long long	*ret;
	size_t				i;

	i = 0;
//	ft_printf("Total bytes in memdup %d\n", bytes);
	ret = ft_memalloc(bytes + 8);
	while (i < bytes)
	{
		ret[i] = stack[i];
		i++;
	}
	return (ret);
}
