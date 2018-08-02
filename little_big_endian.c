/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_big_endian.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 14:38:10 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/02 14:52:05 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		main(void)
{
	int		x;
	char	*a;

	x = 1;
	a = (char*)&x;

	//Big endian
	//00000........ 0000 0001
	
	//Little Endian
	//0000 0001.... 0000 0000

	if(*a == 0)
		printf("You are running a Big Endian machine\n");
	else
		printf("You are running a Little Endian machine\n");

	return (0);
}
