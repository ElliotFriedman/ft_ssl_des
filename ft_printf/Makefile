# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efriedma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/04 17:04:47 by efriedma          #+#    #+#              #
#    Updated: 2018/06/06 14:41:27 by efriedma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -I libft

NAME = libftprintf.a

TRASH = rm -f

LIBFT := libft/

SRC = handle/handle_flags.c \
	  handle/ft_parse.c \
	  print/ft_printf.c \
	  print/ft_print0.c \
	  print/ft_print3.c \
	  print/ft_mputstr.c \
	  print/ft_print2.c \
	  print/ft_print_addy.c \
	  print/ft_printint.c \
	  chars/ft_printchr.c \
	  chars/ft_printwchr.c \


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT)
	@ar rc $(NAME) $(OBJ) libft/*.o
	@ranlib $(NAME) libft/libft.a

clean:
	$(TRASH) $(OBJ)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	$(TRASH) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all
