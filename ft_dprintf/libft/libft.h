/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efriedma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:02:44 by efriedma          #+#    #+#             */
/*   Updated: 2018/05/25 17:13:23 by efriedma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "unistd.h"
# include "stdlib.h"
# include <wchar.h>

typedef struct	s_data
{
	int			negative;
	int			precision;
	int			precheck;
	int			plus;
	int			hash;
	int			sum;
	int			upper;
	int			chrfil;
	int			lr;
	char		mod[2];
	int			len;
	int			iter;
	int			pad;
	int			chk;
	int			fd;
}				t_data;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

char			*ft_uitoabase(unsigned long long nbr, int base);
char			*ft_itoabase(long long nbr, int base);
char			*ft_malset(int size, char set);
wchar_t			*ft_wstrdup(const char *s);
int				ft_wstrlen(wchar_t *str);
void			ft_nwputstr(wchar_t *str, t_data *curr, int i);
void			ft_putwchar(wchar_t c, t_data *curr);
void			ft_wputstr(wchar_t *str, t_data *curr);
void			init(t_data *curr);
char			*upper(char *print);
char			*make_pre(t_data *curr, char *print);
char			*make_pad(t_data *curr, char *print);
char			*prep_x(char *print, char *prep);
int				find_len(const char *str);
int				ft_matoi(const char *str);
void			ft_mputstr(char *str, t_data *curr);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_putnbr_fd(int n, int fd);
void			ft_striter(char *s, void (*f)(char *));
char			*ft_strnew(size_t size);
int				ft_atoi(const char *str);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_putstr(char *str);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *s1, const void *s2, size_t n);
void			ft_putstr_fd(char const *s, int fd);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strrchr(const char *s1, int c);
int				ft_isalnum(int c);
void			ft_memdel(void **ap);
char			*ft_strcat(char *s1, const char *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			**ft_strsplit(char const *s, char c);
int				ft_isalpha(int c);
void			*ft_memmove(void *s1, const void *s2, size_t n);
char			*ft_strchr(const char *s1, int c);
size_t			ft_strlen(const char *str);
char			*ft_strstr(const char *s1, const char *s2);
int				ft_isascii(int c);
void			*ft_memset(void *b, int c, size_t len);
void			ft_strclr(char *s);
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strsub(char const *s, unsigned int start, size_t len);
int				ft_isdigit(int c);
void			ft_putchar(char c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s);
int				ft_isprint(int c);
void			ft_putchar_fd(char c, int fd);
char			*ft_strcpy(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_tolower(int c);
char			*ft_itoa(int n);
void			ft_putendl(char const *s);
void			ft_strdel(char **as);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_toupper(int c);
void			*ft_memalloc(size_t size);
void			ft_putendl_fd(char const *s, int fd);
char			*ft_strdup(const char *s);
char			*ft_strncpy(char *dest, const char *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			ft_putnbr(int n);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstnew(void const *content, size_t content_size);
int				ft_multiply(int a, int b);
int				ft_divide(int a, int b);
int				ft_add(int a, int b);
int				ft_subtract(int a, int b);
char			**ft_getnextline(char *str);
char			*ft_capitalize(char *str);
int				ft_wordcount(char *str);
#endif
