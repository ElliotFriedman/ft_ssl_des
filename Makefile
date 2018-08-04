# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efriedma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/01 16:05:56 by efriedma          #+#    #+#              #
#    Updated: 2018/08/03 18:08:24 by efriedma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#-g -fsanitize=address 

CFLAGS = -Wall -Wextra -I ft_printf/libft -I ft_printf/includes

NAME = ft_ssl

SRCS = main.c \
	des/des.c \
	   base64.c \
	   base64decode.c \
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
	$(MAKE) -C ft_printf
	gcc $(OBJ) ft_printf/libftprintf.a -o ft_ssl


clean:
	@rm $(OBJ)
	$(MAKE) -C ft_printf clean

fclean: clean
	rm $(NAME)
	$(MAKE) -C ft_printf fclean

re: fclean $(NAME)
