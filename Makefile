# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 13:59:01 by jwisozk           #+#    #+#              #
#    Updated: 2019/08/09 14:15:26 by jwisozk          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADERS = RTv1.h
LIBMLX = minilibx/libmlx.a
LIBFT = libft/libft.a
MAKE_LIBFT = make -C libft
MAKE_LIBMLX = make -C minilibx
SOURCE = main.c
OBJ = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE_LIBFT)
	@$(MAKE_LIBMLX)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(LIBMLX) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -pthread -c $<

clean:
	rm -f $(OBJ)
	$(MAKE_LIBFT) clean
	$(MAKE_LIBMLX) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(LIBMLX)

re: fclean all

.PHONY: all fclean re clean
