# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/09 13:59:01 by jwisozk           #+#    #+#              #
#    Updated: 2019/09/29 15:35:22 by jwisozk          ###   ########.fr        #
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
SOURCE =    main.c \
            extra.c \
            draw.c \
            color.c \
            operations_v.c \
            operations_d.c \
            lighting.c \
            light_create.c \
            light_update.c \
            objects_intersect.c \
            objects_fill.c \
            camera.c \
            camera_create.c \
            camera_update.c \
            objects_create.c \
            geometric_create.c \
            transform.c \
            objects_update.c \
            camera_validate.c  \
            objects_validate.c \
            objects_calculate.c \
            light_validate.c \
            scene_get.c \
            scene_extra.c

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
