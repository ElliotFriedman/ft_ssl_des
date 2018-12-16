/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:18:06 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/22 17:18:15 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init(t_data *curr)
{
	curr->plus = 0;
	curr->precheck = 0;
	curr->precision = 0;
	curr->hash = 0;
	curr->upper = 0;
	curr->pad = 0;
	curr->chrfil = 0;
	curr->lr = 0;
	curr->len = 0;
	curr->negative = 0;
	curr->chk = 0;
	ft_bzero(curr->mod, 2);
}
