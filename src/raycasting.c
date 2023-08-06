/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:12:02 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 11:37:03 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static double	get_dist(t_cube *cube, t_player *player, double x, double y);
static void		get_coords(double *x_add, double *y_add, \
	t_player *player, t_cube *cube);
static void		draw_wall(double dist, t_cube *cube, int x, int color);
static int		ft_color(t_player *player, double x, double y, t_cube *cube);

void	ft_raycasting(t_cube *cube, t_player *player)
{
	double	distance;
	double	angle_save;
	int		a;

	fix_angle(player);
	angle_save = player->direction;
	a = 0;
	player->color = BLUE;
	player->direction -= player->fov / 2;
	while (a <= WIN_WIDTH)
	{
		distance = get_dist(cube, player, player->x, player->y);
		distance *= cos(angle_save - player->direction) * FOV;
		draw_wall(distance, cube, a, player->color);
		player->direction += player->fov / WIN_WIDTH;
		fix_angle(player);
		a++;
	}
	player->direction = angle_save;
}

static double	get_dist(t_cube *cube, t_player *player, double x, double y)
{
	player->dist_x = cos(cube->player.direction) * 0.1;
	player->dist_y = sin(cube->player.direction) * 0.1;
	while (1)
	{
		if (ft_valid_pos(cube, x, y) > 0)
		{	
			get_coords(&x, &y, player, cube);
			player->color = ft_color(player, x, y, cube);
			return (ft_distance(x, y, player->x, player->y));
		}
		x += player->dist_x;
		y += player->dist_y;
	}
}

static void	get_coords(double *x_add, double *y_add, \
	t_player *player, t_cube *cube)
{
	double	x;
	double	y;

	x = *x_add;
	y = *y_add;
	while (ft_valid_pos(cube, x, y) > 0)
	{
		x -= player->dist_x * (RESOLUTION * 100);
		y -= player->dist_y * (RESOLUTION * 100);
	}
	while (ft_valid_pos(cube, x, y) < 1)
	{
		x += player->dist_x * (RESOLUTION * 10);
		y += player->dist_y * (RESOLUTION * 10);
	}
	while (ft_valid_pos(cube, x, y) > 0)
	{
		x -= player->dist_x * RESOLUTION;
		y -= player->dist_y * RESOLUTION;
	}
	x += player->dist_x * RESOLUTION;
	y += player->dist_y * RESOLUTION;
	*y_add = y;
	*x_add = x;
}

static int	ft_color(t_player *player, double x, double y, t_cube *cube)
{
	int	color;

	if (cube->map[(int)x][(int)y] == CLOSED_DOOR)
		return (GREEN);
	if (fabs((int)x - x) >= fabs((int)y - y))
	{
		if (abs((int)x) != abs((int)(x - player->dist_x * RESOLUTION)))
			color = PASTEL_LAVENDER;
		else
			color = PASTEL_PEACH;
	}
	else if (fabs((int)x - x) < fabs((int)y - y))
	{
		if (abs((int)x) != abs((int)(x - player->dist_x * RESOLUTION)))
			color = PASTEL_PURPLE;
		else
			color = PASTEL_PINK;
	}
	x = x - player->dist_x * RESOLUTION;
	y = y - player->dist_y * RESOLUTION;
	if (cube->map[(int)(x)][(int)(y)] == OPENED_DOOR)
		color = BLUE;
	return (color);
}

static void	draw_wall(double dist, t_cube *cube, int x, int color)
{
	int		range;
	int		range_start;
	int		y;

	if (dist < 1)
		dist = 1;
	range = WIN_HEIGHT / dist;
	range_start = range / 2;
	while (range)
	{
		y = (WIN_HEIGHT / 2 + range_start - range);
		my_mlx_pixel_put(cube->img, WIN_WIDTH - x, y, color);
		range--;
	}
}
