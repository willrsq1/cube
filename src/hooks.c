/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:21:29 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 11:45:26 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	ft_key_pressed(int key, t_cube *cube);
static void	ft_move_right(t_cube *cube);
static void	ft_move_left(t_cube *cube);
static void	ft_update_image(t_cube *cube);

int	ft_key_hook(int key, t_cube *cube)
{
	cube->player.prev_x = cube->player.x;
	cube->player.prev_y = cube->player.y;
	ft_key_pressed(key, cube);
	if (ft_valid_pos(cube, cube->player.x, cube->player.y) > 0)
	{
		if (!ft_valid_pos(cube, cube->player.prev_x, cube->player.y))
			cube->player.x = cube->player.prev_x;
		else if (!ft_valid_pos(cube, cube->player.x, cube->player.prev_y))
			cube->player.y = cube->player.prev_y;
		else
		{
			cube->player.x = cube->player.prev_x;
			cube->player.y = cube->player.prev_y;
			return (1);
		}
	}
	ft_doors(key, cube);
	ft_update_image(cube);
	return (1);
}

static void	ft_key_pressed(int key, t_cube *cube)
{
	printf("%d\n", key);
	if (key == ESC_KEY)
		ft_free_exit(cube);
	if (key == A_KEY)
		cube->player.direction -= 0.1;
	if (key == Z_KEY)
		cube->player.direction += 0.1;
	if (key == UP_ARROW)
	{
			cube->player.x += cos(cube->player.direction) / 10;
			cube->player.y += sin(cube->player.direction) / 10;
	}
	if (key == DOWN_ARROW)
	{
		cube->player.x -= cos(cube->player.direction) / 10;
		cube->player.y -= sin(cube->player.direction) / 10;
	}
	if (key == RIGHT_ARROW)
		ft_move_right(cube);
	if (key == LEFT_ARROW)
		ft_move_left(cube);
}

static void	ft_move_right(t_cube *cube)
{
	if (cube->player.direction > 0 && cube->player.direction < PI)
	{
		cube->player.x -= cos(cube->player.direction + PI / 2) / 10;
		cube->player.y -= sin(cube->player.direction + PI / 2) / 10;
	}
	else
	{
		cube->player.x += cos(cube->player.direction - PI / 2) / 10;
		cube->player.y += sin(cube->player.direction - PI / 2) / 10;
	}
}

static void	ft_move_left(t_cube *cube)
{
	if (cube->player.direction > 0 && cube->player.direction < PI)
	{
		cube->player.x -= cos(cube->player.direction - PI / 2) / 10;
		cube->player.y -= sin(cube->player.direction - PI / 2) / 10;
	}
	else
	{
		cube->player.x += cos(cube->player.direction + PI / 2) / 10;
		cube->player.y += sin(cube->player.direction + PI / 2) / 10;
	}
}

static void	ft_update_image(t_cube *cube)
{
	cube->img->img_ptr = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cube->img->img_ptr)
	{
		perror("at mlx_new_image in ft_update_image");
		ft_free_exit(cube);
	}
	cube->img->addr = mlx_get_data_addr(cube->img->img_ptr, &cube->img->bpp, \
		&cube->img->size_line, &cube->img->endian);
	ft_draw(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->img->img_ptr, 0, 0);
	mlx_destroy_image(cube->mlx, cube->img->img_ptr);
	cube->img->img_ptr = NULL;
}
