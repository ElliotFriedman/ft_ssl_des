/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:02:27 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/28 01:02:07 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

int					g_file;
int					g_bool;
int					g_fd;
int					g_decrypt;

int					g_ivIdx = -1;
int					g_K = -1;
unsigned long long	g_iv;
size_t				g_ivBool = 0;
//salt should be 8 bytes
unsigned long long	g_salt;
size_t				g_saltidx;
size_t				g_saltbool;

unsigned long long	g_key;
int					g_passidx;
char				*g_pass;

size_t				g_file;
size_t				g_fileidx;

void	err0r(char *msg)
{
	ft_putstr(msg);
	exit(0);
}

void	part2(char *argv, t_opt *new, int i)
{
	if (!ft_strncmp(argv, "-p", 2) && ++g_bool)
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
}

int		opt(char *argv, t_opt *new, int i)
{
	g_bool = 0;
	if (!ft_strncmp(argv, "-nosalt", 7))
		g_salt = 3;
	if (!ft_strncmp(argv, "-v", 3) && ++g_bool)
		g_ivIdx = i + 1;
	if (!ft_strncmp(argv, "-k", 2) && ++g_bool)
		g_K = i + 1;
	if (!ft_strncmp(argv, "-s", 2))
		g_saltidx = i + 1;
	//figure out how to handle this
	//what struct will we store this data in?
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

void	checkbase16(char *str, char *err)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !(str[i] >= 'A' && str[i] <= 'F'))
		{
			ft_printf("invalid hex %s value\n", err);
			exit(0);
		}
		i++;
	}
}

void	handle_iv(char **argv)
{
	char	*tmp;
	char	*tfree;

	tfree = 0;
	tmp = 0;
	checkbase16(argv[g_ivIdx], "iv");
	if (ft_strlen(argv[g_ivIdx]) >= 28)
		err0r("hex string is too long\ninvalid hex iv value\n");
	if (ft_strlen(argv[g_ivIdx]) != 16)
	{
		char *tmpa = ft_strdup(argv[g_ivIdx]);
		while (ft_strlen(tmpa) < 16)
		{
			tfree = tmpa;
			tmpa = ft_strjoin(tmpa, "0");
			free(tfree);
		}
		g_ivBool = 1;
		g_iv = ft_atoibase16(tmpa);
		free(tmpa);
	}
	else
		g_iv = ft_atoibase16(argv[g_ivIdx]);
	g_ivIdx = 0;
}

void	handle_k(char **argv)
{
	char	*tmp;
	char	*tfree;

	tfree = 0;
	tmp = 0;
	checkbase16(argv[g_K], "key");
	if (ft_strlen(argv[g_K]) >= 28)
		err0r("hex string is too long\ninvalid hex key value\n");
	if (ft_strlen(argv[g_K]) != 16)
	{
		char *tmpa = ft_strdup(argv[g_K]);
		while (ft_strlen(tmpa) < 16)
		{
			tfree = tmpa;
			tmpa = ft_strjoin(tmpa, "0");
			free(tfree);
		}
		g_key = ft_atoibase16(tmpa);
		free(tmpa);
	}
	else
		g_key = ft_atoibase16(argv[g_K]);
	g_K = 99999999;
	g_saltbool = 0;
	g_salt = 0;
}

void	handle_salt(char **argv)
{
	g_salt = ft_atoibase16(argv[g_saltidx]);
	g_saltidx = 0;
	g_saltbool = 1;
}

void	get_opt_if(int argc, char **argv)
{
	if (g_K != -1 && g_K != 99999999)
		handle_k(argv);
	if (g_passidx == argc)
		err0r("Error, no password specified\n");
	if (g_passidx && g_passidx != 1000000000)
	{
		g_pass = ft_strdup(argv[g_passidx]);
		g_passidx = 1000000000;
		g_key = 1;
	}
	if (!g_ivBool && g_ivIdx != -1 && g_ivIdx != argc)
		handle_iv(argv);
	else if (g_ivIdx == argc)
		err0r("Error, no iv specified\n");
	if ((int)g_saltidx == argc)
		err0r("Error, no salt specified\n");
	else if (g_saltidx)
		handle_salt(argv);
}

int		get_opt(int argc, char **argv, t_opt *new, int i)
{
	int	fd;

	fd = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-' && (open(argv[i], O_RDONLY) == -1) && opt(argv[i], new, i))
		{
			get_opt_if(argc, argv);
			return (1);
		}
		else if (!g_fd && new->o && ((fd = (open(argv[i], O_RDONLY)) > 2)))
			g_fd = fd;
		i++;
	}
	return (0);
}
