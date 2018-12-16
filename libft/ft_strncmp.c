/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 13:07:06 by efriedma          #+#    #+#             */
/*   Updated: 2018/02/26 12:44:32 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	n--;
	while (s1[i] == s2[i] && s2[i] && s1[i] && i < n)
		i++;
	return (((int)(unsigned char)s1[i]) - ((int)(unsigned char)s2[i]));
}
