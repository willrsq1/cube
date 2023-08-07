/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_raycasting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 12:12:02 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/07 03:48:43 by wruet-su         ###   ########.fr       */
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
	double	angle_save;
	int		a;

	a = 0;
	ft_background(cube);
	fix_angle(player);
	angle_save = player->direction;
	player->color = BLUE;
	player->direction += player->fov / 2;
	while (a <= WIN_WIDTH)
	{
		distance = get_dist(cube, player, player->x, player->y);
		distance *= cos(angle_save - player->direction) * FOV;
		draw_wall(distance, cube, a, player->color);
		player->direction -= player->fov / WIN_WIDTH;
		fix_angle(player);
		a++;
	}
	player->direction = angle_save;
}

static double	get_dist(t_cube *cube, t_player *player, double x, double y)
{
	cube->player.dist_x = cos(cube->player.direction) * 0.01;
	cube->player.dist_y = sin(cube->player.direction) * 0.01;
	while (1)
	{
		if (ft_valid_pos(cube, x, y) > 0)
		{	
			get_exact_coords(&x, &y, cube);
			player->color = ft_color(player, x, y, cube);
			return (ft_distance(x, y, player->x, player->y));
		}
		x += player->dist_x;
		y += player->dist_y;
	}
}

static void	get_exact_coords(double *x, double *y, t_cube *cube)
{
	while (ft_valid_pos(cube, *x, *y) > 0)
	{
		*x -= cube->player.dist_x * (RESOLUTION * 100);
		*y -= cube->player.dist_y * (RESOLUTION * 100);
	}
	while (ft_valid_pos(cube, *x, *y) < 1)
	{
		*x += cube->player.dist_x * (RESOLUTION * 10);
		*y += cube->player.dist_y * (RESOLUTION * 10);
	}
	while (ft_valid_pos(cube, *x, *y) > 0)
	{
		*x -= cube->player.dist_x * RESOLUTION;
		*y -= cube->player.dist_y * RESOLUTION;
	}
	*x += cube->player.dist_x * RESOLUTION;
	*y += cube->player.dist_y * RESOLUTION;
}

static int	ft_color(t_player *player, double x, double y, t_cube *cube)
{
	int	color;

	if (cube->map[(int)x][(int)y] == CLOSED_DOOR)
		return (CD_COLOR);
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
		color = OP_COLOR;
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
		ft_pixel(cube->img, x, y, color);
		range--;
	}
}
