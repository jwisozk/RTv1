# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iplastun <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 13:59:01 by jwisozk           #+#    #+#              #
#    Updated: 2019/09/24 20:47:33 by iplastun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = gcc
CFLAGS = -Wall -Wextra -Werror

HEADERS = RTv1.h
LIBMLX = minilibx/libmlx.a
FRAMEWORKS = -framework OpenGL -framework AppKit
LIBFT = libft/libft.a
MAKE_LIBFT = make -C libft
MAKE_LIBMLX = make -C minilibx
SOURCE = main.c \
        keys.c \
        draw.c \
        color.c \
        operations.c \
        lighting.c \
        intersect_objects.c \
        fill_objects.c \
        matrix.c \
        camera.c \
        create_objects.c \
        create_geometric_values.c \
        create_types.c

OBJ = $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE_LIBFT)
	@$(MAKE_LIBMLX)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(LIBMLX) $(FRAMEWORKS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

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
