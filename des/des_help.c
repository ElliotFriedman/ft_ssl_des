/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 22:36:28 by efriedma          #+#    #+#             */
/*   Updated: 2018/12/15 22:00:48 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../openssl.h"

extern size_t				g_passlen;
extern char					*g_tmp;
extern unsigned long long	g_key;
extern char					*g_saltchars;
extern int					g_saltcharbool;
extern int					g_b64;
extern int					g_decrypt;
extern int					g_cbc;
extern int					g_out;
extern size_t				g_strlen;
extern size_t				g_saltbool;
extern int					g_ka;
extern size_t				g_ivbool;
extern unsigned long long	g_salt;
extern size_t				g_nosalt;
extern char					*g_pass;
extern size_t				g_fileidx;
extern int					g_permute[64];
extern int					g_len;
extern int					g_rotate[16];
extern size_t				g_saltidx;

void						removepadbytes(char *str)
{
	size_t					i;
	size_t					hold;

	i = 7;
	hold = (size_t)(str[i] & 15);
	if (hold == 0 || hold > 8)
	{
		ft_putstr("Bad byte pattern found in padding byte(s)");
		ft_printf(" ascii val %d found\n", hold);
		exit(0);
	}
	g_len -= hold;
	while (i < 8 && ((str[i] & 15) == (hold & 15)))
	{
		str[i] = 0;
		i--;
	}
}

void						checkbase64encode(char *str, size_t bytes)
{
	size_t					i;

	i = 0;
	if (str[bytes - 1] == '\n')
		bytes--;
	while (i < bytes)
	{
		if (((!ft_strchr(g_ref, str[i]) && str[i] != '=')
					|| bytes % 4 != 0) && str[i] != '\n')
		{
			ft_putstr("Error, invalid byte sequence detected");
			ft_putstr(" in base64 encoded string\n");
			exit(0);
		}
		i++;
	}
}

void						inputsanitycheck(t_hash *h)
{
	if (h->bytes % 8 != 0)
	{
		ft_putstr("Error, invalid byte amount in file staged for decryption\n");
		exit(0);
	}
}

void						handle_b64decrypt(t_hash *h)
{
	char					*tmp1;

	tmp1 = h->data;
	removewhitespace(h->data);
	h->bytes = ft_strlen(h->data);
	checkbase64encode(h->data, h->bytes);
	h->data = (char*)base64_decode((unsigned char*)h->data, h->bytes);
	free(tmp1);
	h->bytes = g_b64;
}

void						checksalt(t_hash *h)
{
	char					*tmp;
	char					*dup;

	tmp = 0;
	dup = 0;
	if (h->bytes >= 16)
	{
		if (!ft_strncmp(h->data, "Salted__", 8))
		{
			tmp = h->data;
			dup = ft_memalloc(9);
			ft_memcpy(dup, &h->data[8], 8);
			char2long(&g_salt, (unsigned char*)dup);
			h->data = (char*)
				ft_memdup((unsigned long long*)&h->data[16], h->bytes - 16);
			rev_8byte((char*)&g_salt, 8);
			g_saltbool = 1;
			g_saltidx = 0;
			h->bytes -= 16;
			g_len -= 16;
			free(tmp);
			free(dup);
		}
	}
}
