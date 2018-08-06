# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efriedma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/01 16:05:56 by efriedma          #+#    #+#              #
#    Updated: 2018/08/06 15:14:41 by efriedma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-g -fsanitize=address 
CFLAGS = -g -Wall -Wextra -I ft_printf/libft -I ft_printf/includes ft_dprintf/includes

NAME = ft_ssl

SRCS = main.c \
	   des/des.c \
	   des/des-encrypt.c \
	   base64/base64.c \
	   base64/base64decode.c \
	   helper/des_pad.c \
       helper/pad.c \
       helper/readfile.c \
	   helper/sha256help.c \
	   md5/md5.c \
       md5/md5hash.c \
	   md5/md5n.c \
	   md5_salt/md5.c \
	   md5_salt/md5hash.c \
       helper/get_opt.c \
       sha256/sha256hash.c \
       sha256/sha256.c \
	   sha256/sha256n.c \
	   sha256/sha256n2.c \

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ft_printf/
	$(MAKE) -C ft_dprintf/
	gcc $(OBJ) ft_printf/libftprintf.a ft_dprintf/libftdprintf.a -o ft_ssl

clean:
	@rm -f $(OBJ)
	$(MAKE) -C ft_printf/ clean
	$(MAKE) -C ft_dprintf/ clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ft_printf/ fclean
	$(MAKE) -C ft_dprintf/ fclean

re: fclean all
