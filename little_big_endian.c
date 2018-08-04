/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_big_endian.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 14:38:10 by efriedma          #+#    #+#             */
/*   Updated: 2018/08/03 21:41:57 by efriedma         ###   ########.fr       */
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

	//if we are big endian, the first byte will be 0's
	if(*a == 0)
		printf("You are running a Big Endian machine\n");
	else
		printf("You are running a Little Endian machine\n");
	//if we are little endian, the first byte will be 1

	return (0);
}
