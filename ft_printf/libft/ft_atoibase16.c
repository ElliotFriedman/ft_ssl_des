/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:31:46 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/12 14:57:32 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long		ft_atoibase16(const char *str)
{
	unsigned long long	nbr;

	nbr = 0;
	while (*str && (ft_isdigit((int)*str) || (*str >= 'A' && *str <= 'F')))
	{
		nbr *= 16;
		if (ft_isdigit((int)*str))
			nbr += *str - 48;
		else
			nbr += *str - 55;
		str++;
	}
	return (nbr);
}

int main()
{
	printf("%llu\n", ft_atoibase16("AAAAAAAAAAAFFFF"));

	return 0;
}
