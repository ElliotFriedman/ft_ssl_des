/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:02:27 by efriedma          #+#    #+#             */
/*   Updated: 2018/09/28 00:02:29 by efriedma         ###   ########.fr       */
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

void	part2(char *argv, t_opt *new, int i)
{
	if (!ft_strncmp(argv, "-p", 2) && ++g_bool)
	{
		if (g_passidx)
		{
			ft_putstr("Error, you can only specify a password once\n");
			exit(0);
		}
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
//	if (!ft_strncmp(argv, "-p", 2) && ++g_bool)
//		g_passidx = i + 1;
}

int		opt(char *argv, t_opt *new, int i)
{
	g_bool = 0;
	//g_salt = 3, indicates we don't need salt
	if (!ft_strncmp(argv, "-nosalt", 7))
		g_salt = 3;
	if (!ft_strncmp(argv, "-v", 3) && ++g_bool)
		g_ivIdx = i + 1;
	if (!ft_strncmp(argv, "-k", 2) && ++g_bool)
		g_K = i + 1;
	if (!ft_strncmp(argv, "-s", 2))
		g_saltidx = i + 1;
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
	{
		ft_putstr("hex string is too long\ninvalid hex iv value\n");
		exit(0);
	}
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
		//rev_8byte((char*)&g_iv, 16);
		//printf("\n\nFound IV %016llX in CL argument\n\n\n\n", g_iv);
		free(tmpa);
	}
	else
		g_iv = ft_atoibase16(argv[g_ivIdx]);
	g_ivIdx = 0;
}

void	get_opt_if(int argc, char **argv)
{
	//set g_K to 99 to indicate that we have created our global key
	//Make sure atoibase16 works
	if (g_K != -1 && g_K != 99999999)// && (g_K = 99999999))
	{
		g_key = ft_atoibase16(argv[g_K]);
		g_K = 99999999;
	}
	//if our password index is beyond command line arguments and therefore non-existent
	if (g_passidx == argc)
	{
		ft_putstr("Error, no password specified\n");
		exit(0);
	}
	if (g_passidx && g_passidx != 1000000000)
	{
		g_pass = ft_strdup(argv[g_passidx]);
		//this will indicate that our password was in the command line args
		g_passidx = 1000000000;
		g_key = 1;
	}
	if (!g_ivBool && g_ivIdx != -1 && g_ivIdx != argc)
		handle_iv(argv);
	else if (g_ivIdx == argc)
	{
		ft_putstr("Error, no iv specified\n");
		exit(0);
	}
	if ((int)g_saltidx == argc)
	{
		ft_putstr("Error, no salt specified\n");
		exit(0);
	}
	else if (g_saltidx)
	{
		g_salt = ft_atoibase16(argv[g_saltidx]);
		g_saltidx = 0;
		g_saltbool = 1;
	}
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
