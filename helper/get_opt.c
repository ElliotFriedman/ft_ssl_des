/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:02:27 by efriedma          #+#    #+#             */
/*   Updated: 2018/12/15 21:59:13 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int					g_file;
int					g_bool;
int					g_fd;
int					g_decrypt;
int					g_ividx = -1;
int					g_ka = -1;
unsigned long long	g_iv;
size_t				g_ivbool = 0;
unsigned long long	g_salt;
size_t				g_saltidx;
size_t				g_saltbool;
size_t				g_nosalt;
unsigned long long	g_key;
int					g_passidx;
char				*g_pass;
size_t				g_fileidx;
int					g_out = 1;
int					g_outbool;
char				*g_tmpa;

void	err0r(char *msg)
{
	ft_putstr(msg);
	exit(0);
}

void	part2(char *argv, t_opt *new, int i)
{
	if (!ft_strncmp(argv, "-p", 2) && ++g_bool && !g_passidx)
	{
		if (g_passidx)
			err0r("Error, you can only specify a password once\n");
		g_passidx = 1 + i;
		new->p = 1;
	}
	if (ft_strchr(argv, (int)'p') && ++g_bool)
		new->p = 1;
	if (ft_strchr(argv, (int)'q') && ++g_bool)
		new->q = 1;
	if (ft_strchr(argv, (int)'r') && ++g_bool)
		new->r = 1;
	if (ft_strchr(argv, (int)'s') && ++g_bool)
		new->s = 1;
	if (((!ft_strncmp(argv, "-D", 2)) ||
				!ft_strncmp(argv, "-d", 2)) && ++g_bool && ++g_decrypt)
		new->d = 1;
	if (!ft_strncmp(argv, "-a", 2) && ++g_bool)
		new->a = 1;
	if (!ft_strncmp(argv, "-o", 2))
		g_outbool = i + 1;
}

int		opt(char *argv, t_opt *new, int i)
{
	g_bool = 0;
	if (!ft_strncmp(argv, "-nosalt", 7) && ++g_bool)
		g_nosalt = 1;
	if (!ft_strncmp(argv, "-v", 3) && ++g_bool)
		g_ividx = i + 1;
	if (!ft_strncmp(argv, "-k", 2) && ++g_bool)
		g_ka = i + 1;
	if (!ft_strncmp(argv, "-s", 2) && ++g_bool)
		g_saltidx = i + 1;
	if (!ft_strncmp(argv, "-i", 2))
		g_fileidx = 1 + i;
	part2(argv, new, i);
	if (ft_strchr(argv, (int)'o') && ++g_bool)
	{
		new->o = 1;
		g_file = ++i;
	}
	if (g_bool)
	{
		new->on = 1;
		return (1);
	}
	return (0);
}

void	get_opt_if(int argc, char **argv)
{
	if (g_ka != -1 && g_ka != 99999999)
		handle_k(argv);
	if (g_passidx == argc)
		err0r("Error, no password specified\n");
	if (g_passidx && g_passidx != 1000000000)
	{
		g_pass = ft_strdup(argv[g_passidx]);
		g_passidx = 1000000000;
		g_key = 1;
	}
	if (!g_ivbool && g_ividx != -1 && g_ividx != argc && g_ividx)
		handle_iv(argv);
	else if (g_ividx == argc)
		err0r("Error, no iv specified\n");
	if ((int)g_saltidx == argc)
		err0r("Error, no salt specified\n");
	if (g_saltidx && !g_saltbool)
		handle_salt(argv);
	if (g_out == argc)
		err0r("Error, no out file specified\n");
	else if (g_outbool && g_out == 1)
	{
		g_out = open(argv[g_outbool], O_TRUNC | O_RDWR | O_CREAT);
		g_outbool = 0;
	}
}

int		get_opt(int argc, char **argv, t_opt *new, int i)
{
	if (i < argc)
	{
		if (argv[i][0] == '-' && opt(argv[i], new, i))
			get_opt_if(argc, argv);
		return (1);
	}
	return (0);
}
