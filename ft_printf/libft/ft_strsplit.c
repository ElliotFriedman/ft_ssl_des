/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 16:12:11 by efriedma          #+#    #+#             */
/*   Updated: 2018/03/04 13:55:07 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cnt_words(const char *s, char c)
{
	int	ctr;
	int i;

	i = 0;
	ctr = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == 0))
			ctr++;
		i++;
	}
	return (ctr);
}

static int	wordlen(const char *s, char c)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i + x] != c && s[i + x])
		x++;
	return (x);
}

static void	set_dptr(const char *s, char **dptr, int *i, char c)
{
	int		len;

	len = 0;
	while (*i < cnt_words(s, c))
	{
		while (s[len] == c)
			len++;
		dptr[*i] = ft_strsub(&s[len], 0, wordlen(&s[len], c));
		len += wordlen(&s[len], c);
		*i += 1;
	}
	dptr[*i] = 0;
}

char		**ft_strsplit(const char *s, char c)
{
	char	**dptr;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!s)
	{
		dptr = (char**)malloc(sizeof(char *));
		dptr[0] = 0;
		return (dptr);
	}
	if (!(dptr = (char**)malloc(sizeof(char *) * (cnt_words(s, c) + 1))))
		return (0);
	set_dptr(s, dptr, &i, c);
	return (dptr);
}
