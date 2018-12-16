/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:42:41 by efriedma          #+#    #+#             */
/*   Updated: 2018/10/15 20:22:52 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENSSL_H
# define OPENSSL_H
# include "ft_printf/includes/ft_printf.h"
# include "ft_printf/libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <pwd.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

# define RR(a, shift) ((a >> shift) | (a << (32 - shift)))
# define RN(a, shift) (a >> shift)
# define LN(a, shift) (a << shift)

const char				g_ref[64];
int						g_fd;

typedef struct			s_hash
{
	char				*name;
	size_t				fd;
	unsigned long long	ini;
	char				*data;
	size_t				bytes;
	unsigned int		*arr;
	unsigned int		end;
	unsigned int		pipe;
	unsigned int		sha;
	size_t				i;
}						t_hash;

typedef	struct			s_type
{
	char				*name;
	void				*ptr;
}						t_type;

typedef struct			s_opt
{
	int					on;
	int					p;
	int					q;
	int					r;
	int					s;
	int					d;
	int					e;
	int					i;
	int					o;
	int					a;
}						t_opt;

typedef struct			s_val
{
	unsigned int		a0;
	unsigned int		b0;
	unsigned int		c0;
	unsigned int		d0;
}						t_val;

typedef struct			s_iter
{
	unsigned int		aa;
	unsigned int		bb;
	unsigned int		cc;
	unsigned int		dd;
	unsigned int		ff;
	unsigned int		i;
	unsigned int		g;
	unsigned int		d;
}						t_iter;

typedef struct			s_sha
{
	unsigned int		a;
	unsigned int		b;
	unsigned int		c;
	unsigned int		d;
	unsigned int		e;
	unsigned int		f;
	unsigned int		g;
	unsigned int		h;
	unsigned int		temp1;
	unsigned int		temp2;
	unsigned int		s0;
	unsigned int		s1;
	unsigned int		ss1;
	unsigned int		ss0;
	unsigned int		maj;
	unsigned int		ch;
	unsigned int		h0;
	unsigned int		h1;
	unsigned int		h2;
	unsigned int		h3;
	unsigned int		h4;
	unsigned int		h5;
	unsigned int		h6;
	unsigned int		h7;
}						t_sha;

unsigned long long		*create_key(t_hash *h);
unsigned long long		*hash_pass(t_hash *h);
int						rstdin(t_hash *h);
int						get_opt(int argc, char **argv, t_opt *new, int i);
void					md5hash(char *str);
void					sha256hash(t_hash *hs, t_opt *nopt);
void					hash(t_hash *h, t_opt *new);
void					sha256start(char **argv, int argc);
void					des(char **argv, int argc);
void					md5start(char **argv, int argc);
unsigned char			*base64_decode(unsigned char *str, int len);
void					base64start(char **argv, int argc);
void					sha256(char	**argv, int argc);
void					epad(t_hash *h);
void					handle_out1(t_sha *s, t_hash *h, t_opt *n);
void					whiled(t_sha *n, size_t i, unsigned int *w);
void					t_sha_init(t_sha *n, unsigned int **w);
void					error(void);
int						fstruct(t_opt *opt, t_hash *h);
void					init_a(t_hash **h, t_opt **s, int *file);
size_t					get_opt_loopb(size_t i, int a, char **av, t_opt *s);
int						seta(t_hash *h, t_opt *s);
int						rkey(t_hash *h);
int						ft_fread(char *str, t_hash *h);
void					p1(char **argv, t_hash *h);
void					set_n_run(t_hash *h, t_opt *s);
int						one_two(int argc, t_opt *s, t_hash *h);
int						do_one(t_opt *s, t_hash *h, int *file);
size_t					get_opt_loop(size_t i, int argc, char **argv, t_opt *s);
void					zer0h(t_opt *h, t_hash *hash);
int						s256hash(char *hash1, t_hash *h, t_opt *s);
void					err(void);
void					swap(t_hash *h);
void					ffstruct(t_opt *opt, t_hash *h);

unsigned long long		*des_encrypt(unsigned long long a, char *b, size_t c);
char					*des_pad(char *encrypt, size_t len);
void					rev_8byte(char *data, size_t len);
unsigned long long		init_subkey(unsigned long long key);
void					rev_8byte(char *data, size_t len);
char					*des_pad(char *encrypt, size_t len);
unsigned long long		pow2(size_t amt);
unsigned long long		initial_perm(unsigned long long textblock);
unsigned long long		pperm(unsigned long long txtblock);
unsigned char			*base64_encode(unsigned char *str, int len);
void					init_a_des(t_hash **h, t_opt **s, int *file);
void					err0r(char *msg);
void					printcommands(char *str);
unsigned long long		init_subkey(unsigned long long key);
unsigned long long		sub_block(unsigned long long key);
unsigned long long		pow2(size_t amt);
void					create_salt(t_hash *h, char *salt);
void					handle_salt_add(t_hash *h);
t_hash					*get_pass_salt(void);
char					*getsalt(t_hash *h, char *salt);
void					removepadbytes(char *str);
void					checksalt(t_hash *h);
void					handle_b64decrypt(t_hash *h);
void					inputsanitycheck(t_hash *h);
void					checkbase64encode(char *str, size_t bytes);
void					iverror(void);
void					freetmp(unsigned long long *tmp);
void					handle_salt(char **argv);
void					handle_k(char **argv);
void					handle_iv(char **argv);
void					checkbase16(char *str, char *err);
unsigned char			*base64_encode(unsigned char *s, int len);
void					choice00(unsigned char *h, t_hash *stor);
void					choice01(unsigned char *h, t_hash *stor);
void					err0rr(char error);
unsigned long long		permuterightside(unsigned long long rside);
unsigned long long		initialperm(unsigned long long txt);
unsigned long long		permute_concatsubkeys(size_t x);
void					concat_subkeys(void);
unsigned long long		comp_perm(unsigned long long i56bit);
size_t					c_num(size_t num);
void					create_subkeys(unsigned long long key);
void					init_txtblock(unsigned long long *a, unsigned char *b);
unsigned long long		sboxes(unsigned long long expandrside);
unsigned long long		final_permutate(unsigned long long rside);
char					*encrypted_des(char *data, unsigned long long key);
unsigned long long		char2long(unsigned long long *b, unsigned char *chr);
int						get_hash_opt(int argc, char **argv, t_opt *n, int i);

#endif
