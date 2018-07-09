/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 10:32:42 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/22 10:32:50 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*prep_x(char *print, char *prep)
{
	char	*tmp;

	tmp = print;
	print = ft_strjoin(prep, print);
	ft_memdel((void**)&tmp);
	return (print);
}
