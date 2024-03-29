cmake_minimum_required(VERSION 3.14)
project(RTv1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(LIBMLX ${CMAKE_SOURCE_DIR}/minilibx/libmlx.a)
find_library(OPENGL OpenGL)
find_library(APPKIT AppKit)
set(SOURCE_FILES
        libft/ft_atoi.c
        libft/ft_atoi_base.c
        libft/ft_bzero.c
        libft/ft_del.c
        libft/ft_free_all.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_isspace.c
        libft/ft_itoa.c
        libft/ft_lstadd.c
        libft/ft_lstadd_back.c
        libft/ft_lstdel.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_memalloc.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memdel.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar.c
        libft/ft_putchar_fd.c
        libft/ft_putendl.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr.c
        libft/ft_putstr_fd.c
        libft/ft_strcat.c
        libft/ft_strchr.c
        libft/ft_strclr.c
        libft/ft_strcmp.c
        libft/ft_strcpy.c
        libft/ft_strdel.c
        libft/ft_strdup.c
        libft/ft_strequ.c
        libft/ft_striter.c
        libft/ft_striteri.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlen.c
        libft/ft_strmap.c
        libft/ft_strmapi.c
        libft/ft_strncat.c
        libft/ft_strncmp.c
        libft/ft_strncpy.c
        libft/ft_strnequ.c
        libft/ft_strnew.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strrev.c
        libft/ft_strsplit.c
        libft/ft_strstr.c
        libft/ft_strsub.c
        libft/ft_strtrim.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/get_next_line.c
        libft/libft.h
        main.c rtv1.h etc_1.c draw.c lighting.c operations_v.c color.c objects_intersect.c objects_fill.c camera.c objects_create.c geometric_create.c camera_create.c libft/ft_atof.c camera_validate.c objects_update.c transform.c operations_d.c scene_get.c scene_extra.c objects_validate.c camera_update.c light_create.c light_update.c light_validate.c objects_calculate.c libft/ft_gc.h libft/ft_gc.c libft/ft_malloc.c libft/ft_clean.c objects_update_min.c)
add_executable(RTv1 ${SOURCE_FILES})
target_link_libraries(RTv1 ${LIBMLX} ${OPENGL} ${APPKIT})