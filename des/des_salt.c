/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_salt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 22:17:58 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/16 22:08:48 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

extern unsigned long long	g_key;
extern size_t				g_salt;
extern char					*g_pass;
extern int					g_decrypt;
extern size_t				g_nosalt;
extern size_t				g_saltbool;

int					char_rand0(FILE *e)
{
	unsigned int			a;

	a = (unsigned int)getc(e);
	while ((a & 127) < 32)
		a += (unsigned int)getc(e);
	return ((int)a);
}

void				create_salt_8bytes(char *salt, FILE *e)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		salt[i] = (char)char_rand0(e) & 127;
		i++;
	}
	salt[8] = 0;
}

void				get_user_pass(char **pass, t_hash *file)
{
	char					*tmpa;

	*pass = ft_strdup(getpass("Enter your password:"));
	tmpa = ft_strdup(getpass("Verifying - Enter your password:"));
	if (ft_strcmp(*pass, tmpa) != 0)
	{
		ft_putstr("Verify failure\nbad password read\n");
		free(tmpa);
		free(*pass);
		free(file->data);
		exit(0);
	}
	free(tmpa);
}

char				*getsalt(t_hash *h, char *salt)
{
	char					*tmp;
	FILE					*e;

	tmp = 0;
	e = fopen("/dev/urandom", "r");
	create_salt_8bytes(salt, e);
	if (!g_nosalt)
	{
		h->data = ft_memjoin(h->data, salt, ft_strlen(h->data), 8);
		h->bytes += 8;
	}
	if (!g_decrypt)
	{
		tmp = ft_strjoin("Salted__", salt);
	}
	fclose(e);
	return (tmp);
}

t_hash				*get_pass_salt(void)
{
	char					salt[9];
	char					*pass;
	t_hash					*h;

	h = ft_memalloc(sizeof(t_hash));
	pass = 0;
	if (!g_key)
	{
		get_user_pass(&pass, h);
		g_pass = pass;
		h->data = pass;
		h->bytes = ft_strlen(pass);
	}
	else
	{
		pass = g_pass;
		h->data = pass;
		h->bytes = ft_strlen(h->data);
	}
	if (!g_nosalt && !g_decrypt && !g_saltbool)
		create_salt(h, salt);
	else if (!g_nosalt && g_saltbool)
		handle_salt_add(h);
	return (h);
}
