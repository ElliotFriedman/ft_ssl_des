/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:04:29 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/15 15:57:10 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

extern int					g_file;
extern int					g_bool;
extern int					g_fd;
extern int					g_decrypt;
extern int					g_ividx;
extern int					g_ka;
extern unsigned long long	g_iv;
extern size_t				g_ivbool;
extern unsigned long long	g_salt;
extern size_t				g_saltidx;
extern size_t				g_saltbool;
extern size_t				g_nosalt;
extern unsigned long long	g_key;
extern int					g_passidx;
extern char					*g_pass;
extern size_t				g_fileidx;
extern int					g_out;
extern int					g_outbool;
extern char					*g_tmpa;

void			checkbase16(char *str, char *err)
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

void			handle_iv(char **argv)
{
	char	*tmp;
	char	*tfree;

	tfree = 0;
	tmp = 0;
	checkbase16(argv[g_ividx], "iv");
	if (ft_strlen(argv[g_ividx]) >= 28)
		err0r("hex string is too long\ninvalid hex iv value\n");
	if (ft_strlen(argv[g_ividx]) != 16)
	{
		g_tmpa = ft_strdup(argv[g_ividx]);
		while (ft_strlen(g_tmpa) < 16)
		{
			tfree = g_tmpa;
			g_tmpa = ft_strjoin(g_tmpa, "0");
			free(tfree);
		}
		g_ivbool = 1;
		g_iv = ft_atoibase16(g_tmpa);
		free(g_tmpa);
	}
	else
		g_iv = ft_atoibase16(argv[g_ividx]);
	g_ividx = 0;
}

void			handle_k(char **argv)
{
	char	*tmp;
	char	*tfree;

	tfree = 0;
	tmp = 0;
	checkbase16(argv[g_ka], "key");
	if (ft_strlen(argv[g_ka]) >= 28)
		err0r("hex string is too long\ninvalid hex key value\n");
	if (ft_strlen(argv[g_ka]) != 16)
	{
		g_tmpa = ft_strdup(argv[g_ka]);
		while (ft_strlen(g_tmpa) < 16)
		{
			tfree = g_tmpa;
			g_tmpa = ft_strjoin(g_tmpa, "0");
			free(tfree);
		}
		g_key = ft_atoibase16(g_tmpa);
		free(g_tmpa);
	}
	else
		g_key = ft_atoibase16(argv[g_ka]);
	g_ka = 99999999;
	g_saltbool = 0;
	g_salt = 0;
}

void			handle_salt(char **argv)
{
	char	*tmpa;
	char	*tfree;

	tmpa = 0;
	tfree = 0;
	checkbase16(argv[g_saltidx], "salt");
	if (ft_strlen(argv[g_saltidx]) >= 28)
		err0r("hex string is too long\ninvalid hex salt value\n");
	if ((ft_strlen(argv[g_saltidx]) != 16))
	{
		tmpa = ft_strdup(argv[g_saltidx]);
		while (ft_strlen(tmpa) < 16)
		{
			tfree = tmpa;
			tmpa = ft_strjoin(tmpa, "0");
			free(tfree);
		}
		g_salt = ft_atoibase16(tmpa);
		free(tmpa);
	}
	else
		g_salt = ft_atoibase16(argv[g_saltidx]);
	rev_8byte((char*)&g_salt, 8);
	g_saltidx = 0;
	g_saltbool = 1;
}
