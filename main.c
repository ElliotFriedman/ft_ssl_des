/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 15:34:21 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/27 00:38:27 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

const int	g_total = 6;
int			g_cbc;

void	init_command(t_type **arr, size_t index, char *str, void *command)
{
	arr[index]->name = ft_strdup(str);
	arr[index]->ptr = command;
}

t_type	**create(t_type **s)
{
	size_t	i;

	i = 0;
	s = ft_memalloc(sizeof(t_type) * g_total);
	while (i < g_total)
	{
		s[i] = ft_memalloc(sizeof(t_type));
		i++;
	}
	init_command(s, 0, "md5", md5start);
	init_command(s, 1, "sha256", sha256start);
	init_command(s, 2, "base64", base64start);
	init_command(s, 3, "des", des);
	init_command(s, 4, "des-cbc", des);
	init_command(s, 5, "des-ecb", des);
	return (s);
}

int		dispatch(t_type *t, int argc, char **argv)
{
	void (*x) (char**, int);

	if (!ft_strcmp(t->name, argv[1]))
	{
		x = (void (*)(char**, int))(t->ptr);
		if (!ft_strcmp(t->name, "des-cbc") || !ft_strcmp(t->name, "des-cbc"))
			g_cbc = 1;
		x(argv, argc);
		return (1);
	}
	return (0);
}

void	free_struct(t_type **done)
{
	size_t	i;

	i = 0;
	while (i < g_total)
	{
		free(done[i]->name);
		i++;
	}
	ft_memdel((void**)done);
}

int		main(int argc, char **argv)
{
	t_type	**s;
	size_t	i;

	i = 0;
	s = 0;
	if (argc >= 2)
	{
		s = create(s);
		i = 0;
		while (i < g_total && ft_strcmp(s[i]->name, argv[1]))
			i++;
		if (i == g_total || !dispatch(s[i], argc, argv))
		{
			ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
			ft_printf("\nStandard commands:\n\nMessage Digest commands:\nmd5\nsha256\n\n");
			ft_putstr("Cipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\n\n");
		}
		free_struct(s);
	}
	else
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}
