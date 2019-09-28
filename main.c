/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 13:37:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/09/29 00:27:14 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		ft_print_error(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
	exit(0);
}

void	ft_init_shapes(t_data *data)
{
	data->sphere = NULL;
	data->plane = NULL;
	data->cylinder = NULL;
	data->cone = NULL;
	data->p = ft_create_point();
	data->o = NULL;
	data->l = NULL;
	data->cam = NULL;
}

void	ft_open_window(t_data *data)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, DW, DH, "RTv1");
	data->img.img_ptr = mlx_new_image(mlx_ptr, DW, DH);
	data->img.img_arr = (int*)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bit_per_pixel, &data->img.size_line, &data->img.endian);
	data->mlx_ptr = mlx_ptr;
	data->win_ptr = win_ptr;
	ft_draw(data);
	mlx_hook(win_ptr, 17, 0, ft_close_window, data);
	mlx_hook(win_ptr, 2, 0, ft_key_press, data);
//	mlx_hook(win_ptr, 4, 0, ft_mouse_press, p);
//	mlx_hook(win_ptr, 5, 0, ft_mouse_release, p);
//	mlx_hook(win_ptr, 6, 0, ft_mouse_move, p);
	mlx_loop(mlx_ptr);
}

t_lst *ft_new_lst(char *type, void *data)
{
	t_lst *lst;

	lst = (t_lst*)malloc(sizeof(t_lst));
	lst->type = type;
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

void  ft_add_lst(t_lst **head, t_lst *new)
{
	if (head != NULL && new != NULL)
	{
		new->next = *head;
		*head = new;
	}
}

double *ft_new_arr_d(char *a, char *b, char *c)
{
	double *arr;

	arr = (double *)malloc(sizeof(double) * 3);
	arr[0] = ft_atof(a);
	arr[1] = ft_atof(b);
	arr[2] = ft_atof(c);
	return (arr);
}

int *ft_rotation_order(int *arr, int array[3], char *str)
{
	char *pattern = "xyz";
	int i;
	int j;

	if (ft_strlen(str) != 3)
		ft_print_error("Error: the length of the 4th parameter of rotation should be equal to 3");
	if (ft_strchr(str, 'x') == NULL || ft_strchr(str, 'y') == NULL || ft_strchr(str, 'z') == NULL)
		ft_print_error("Error: the 4th parameter of rotation is invalid");
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (str[i] == pattern[j])
				arr[j] = array[i];
			j++;
		}
		i++;
	}
	return (arr);
}

int *ft_new_arr_i(char *a, char *b, char *c, char *str)
{
	int *arr;
	int array[3];

	array[0] = ft_atoi(a);
	array[1] = ft_atoi(b);
	array[2] = ft_atoi(c);
	arr = (int *)malloc(sizeof(int) * 3);
	if (str != NULL)
		arr = ft_rotation_order(arr, array, str);
	else
	{
		arr[0] = array[0];
		arr[1] = array[1];
		arr[2] = array[2];
	}
	return (arr);
}

void  ft_add_obj(t_obj **head, t_obj *new)
{
	if (head != NULL && new != NULL)
	{
		new->next = *head;
		*head = new;
	}
}
void ft_create_objects(t_data *data)
{
	if (data->sphere != NULL)
		data->o = ft_create_object(data->sphere, SPHERE);
	if (data->plane != NULL)
	{
		if (data->o == NULL)
			data->o = ft_create_object(data->plane, PLANE);
		else
			ft_add_obj(&data->o, ft_create_object(data->plane, PLANE));
	}
	if (data->cylinder != NULL)
	{
		if (data->o == NULL)
			data->o = ft_create_object(data->cylinder, CYLINDER);
		else
			ft_add_obj(&data->o, ft_create_object(data->cylinder, CYLINDER));
	}
	if (data->cone != NULL)
	{
		if (data->o == NULL)
			data->o = ft_create_object(data->cone, CONE);
		else
			ft_add_obj(&data->o, ft_create_object(data->cone, CONE));
	}
}

void	ft_check_braces(int block, int n)
{
	int err;

	err = 0;
	if (block > 0 && n == 1)
		err = 1;
	if (block == 0 && n == 2)
		err = 1;
	if (block != 0 && n == 3)
		err = 1;
	if (err == 1)
		ft_print_error("Error: curly braces in the file are not valid");
}

void ft_get_scene(int fd, t_data *data)
{
	char	*line;
	int		i;
	int 	j;
	char	**str;
	char 	*type;
	static t_arr_type arr[] = ARR_TYPES;
	int 	max;
	t_lst	*lst;
	t_lst	*tmp;
	int 	block;
	int 	t;

	t = 0;
	lst = NULL;
	type = NULL;
	block = 0;
	max = sizeof(arr) / sizeof(t_arr_type);
	while (get_next_line(fd, &line) > 0)
	{
		while (ft_isspace(*line) == 1)
			line++;
		if (*line == '\0')
			continue ;
		if (*line == '#')
		{
			type = ft_strsplit(line + 1, ' ')[0];
			if (type == NULL || t > 0)
				ft_print_error("Error: type # is invalid");
			i = 0;
			while (i < max && ft_strequ(type, arr[i].type) != 1)
				i++;
			t++;
			continue ;
		}
		if (*line == '{')
		{
			ft_check_braces(block, 1);
			block++;
		}
		else if (*line == '}')
		{
			if (lst != NULL)
				arr[i].ft_create_type(data, lst);
			lst = NULL;
			ft_check_braces(block, 2);
			block--;
			t--;
		}
		else if (block == 1 && (str = ft_strsplit(line, ' '))[0] != NULL)
		{
			j = 0;
			while (str[j] != NULL)
				j++;
			if (j == 2)
				tmp = ft_new_lst(str[0], str[1]);
			else if (j == 5 && ft_strequ(str[0], "rotation"))
				tmp = ft_new_lst(str[0], ft_new_arr_i(str[1], str[2], str[3], str[4]));
			else if (ft_strequ(str[0], "color") || ft_strequ(str[0], "rotation"))
				tmp = ft_new_lst(str[0], ft_new_arr_i(str[1], str[2], str[3], NULL));
			else
				tmp = ft_new_lst(str[0], ft_new_arr_d(str[1], str[2], str[3]));
			ft_add_lst(&lst, tmp);
		}
	}
	ft_check_braces(block, 3);
	ft_create_objects(data);
}

int main(int argc, char **argv)
{
	int		fd;
	t_data	data;

	if (argc == 2)
	{
		if (ft_strnequ(ft_strrev(argv[1]), ft_strrev(EXTENSION), 4) != 1)
			ft_print_error("Error: invalid file");
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			return (ft_print_error("Error: file not found"));
		ft_init_shapes(&data);
		ft_get_scene(fd, &data);
		ft_check_valid(&data);
		ft_open_window(&data);
	}
	else
		ft_print_error("Usage: ./fdf <filename>");
	return (0);
}