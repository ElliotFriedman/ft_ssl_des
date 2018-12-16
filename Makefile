# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efriedma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/01 16:05:56 by efriedma          #+#    #+#              #
#    Updated: 2018/10/15 20:23:14 by efriedma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GARBAGE = ft_dprintf/libftdprintf.a ft_dprintf/libftdprintf.a 

DEBUG_FLAGS = -g -fsanitize=address
CFLAGS = -Werror -Wall -Wextra -I ft_printf/libft -I ft_printf/includes

NAME = ft_ssl

SRCS = main.c des/des.c des/des_encrypt.c des/encrypt64bits.c des/pbox.c helper/error.c
SRCS += des/des_salt_help.c des/des_salt.c base64/base64.c  base64/base64decode.c helper/des_pad.c
SRCS += helper/pad.c helper/readfile.c helper/sha256help.c md5/md5.c md5/md5hash.c md5/md5n.c
SRCS += md5_salt/md5.c md5_salt/md5hash.c helper/get_opt.c sha256/sha256hash.c sha256/sha256.c
SRCS += helper/hash_opt.c des/des_help.c sha256/sha256n.c sha256/sha256n2.c helper/get_opt2.c
SRCS += base64/base64help.c des/des_permute.c des/des_help2.c des/des_help3.c

all: $(NAME)

go:
	gcc $(SRCS) $(CFLAGS) $(DEBUG_FLAGS) ft_printf/libftprintf.a -o ft_ssl

$(NAME):
	$(MAKE) -C ft_printf/
	gcc $(SRCS) $(CFLAGS) ft_printf/libftprintf.a -o ft_ssl

clean:
	$(MAKE) -C ft_printf/ clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ft_printf/ fclean

re: fclean all
