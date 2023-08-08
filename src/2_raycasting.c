/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_raycasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:12:02 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/08 16:17:21 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static double	get_dist(t_cube *cube, t_player *player, double x, double y);
static void		get_exact_coords(double *x, double *y, t_cube *cube);
static void		draw_wall(double dist, t_cube *cube, int x, int color);
static int		ft_color(t_player *player, double x, double y, t_cube *cube);

void	ft_raycasting(t_cube *cube, t_player *player)
{
	double	distance;
	double	angle;
	int		pixel_column;

	fix_angle(&player->direction);
	pixel_column = 0;
	angle = player->direction + player->fov / 2;
	while (pixel_column <= WIN_WIDTH)
	{
		angle -= player->fov / WIN_WIDTH;
		player->vector_x = cos(angle) * 0.01;
		player->vector_y = sin(angle) * 0.01;
		distance = get_dist(cube, player, player->x, player->y);
		distance *= cos(player->direction - angle) * player->fov;
		draw_wall(distance, cube, pixel_column, player->color);
		pixel_column++;
	}
}

static double	get_dist(t_cube *cube, t_player *player, double x, double y)
{
	double	distance;

	while (ft_valid_pos(cube, x, y) < 1)
	{
		x += player->vector_x;
		y += player->vector_y;
	}
	get_exact_coords(&x, &y, cube);
	player->color = ft_color(player, x, y, cube);
	distance = ft_distance(x, y, player->x, player->y);
	return (distance);
}

static void	get_exact_coords(double *x, double *y, t_cube *cube)
{
	while (ft_valid_pos(cube, *x, *y) > 0)
	{
		*x -= cube->player.vector_x * (RESOLUTION * 100);
		*y -= cube->player.vector_y * (RESOLUTION * 100);
	}
	while (ft_valid_pos(cube, *x, *y) < 1)
	{
		*x += cube->player.vector_x * (RESOLUTION * 10);
		*y += cube->player.vector_y * (RESOLUTION * 10);
	}
	while (ft_valid_pos(cube, *x, *y) > 0)
	{
		*x -= cube->player.vector_x * RESOLUTION;
		*y -= cube->player.vector_y * RESOLUTION;
	}
	*x += cube->player.vector_x * RESOLUTION;
	*y += cube->player.vector_y * RESOLUTION;
}

static int	ft_color(t_player *player, double x, double y, t_cube *cube)
{
	int	color;

	if (cube->map[(int)x][(int)y] == CLOSED_DOOR)
		color = CD_COLOR;
	else if (fabs((int)x - x) >= fabs((int)y - y))
	{
		if (abs((int)x) != abs((int)(x - player->vector_x * RESOLUTION)))
			color = PASTEL_LAVENDER;
		else
			color = PASTEL_PEACH;
	}
	else
	{
		if (abs((int)x) != abs((int)(x - player->vector_x * RESOLUTION)))
			color = PASTEL_PURPLE;
		else
			color = PASTEL_PINK;
	}
	x -= player->vector_x * RESOLUTION;
	y -= player->vector_y * RESOLUTION;
	if (cube->map[(int)(x)][(int)(y)] == OPENED_DOOR)
		color = OP_COLOR;
	return (color);
}

static void	draw_wall(double dist, t_cube *cube, int x, int color)
{
	int		wall_size;
	int		half_of_wall_size;
	int		y;

	if (dist < 1)
		dist = 1;
	wall_size = WIN_HEIGHT / dist;
	half_of_wall_size = wall_size / 2;
	y = 0;
	while (y < WIN_HEIGHT / 2 - half_of_wall_size + cube->height)
	{
		ft_pixel(cube->img, x, y, cube->ceiling_color);
		y++;
	}
	while (y <= WIN_HEIGHT / 2 + half_of_wall_size + cube->height)
	{
		ft_pixel(cube->img, x, y, color);
		y += 1;
	}
	while (y <= WIN_HEIGHT)
	{
		ft_pixel(cube->img, x, y, cube->floor_color);
		y += 1;
	}
}
