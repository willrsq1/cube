/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_img_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 05:40:06 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/12 18:38:25 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cube_bonus.h"

static void	ft_pollution(t_cube *cube, int **map);
static void	ft_propagate_pollution(t_cube *cube, int **map);
static void	ft_convert_enemy(t_cube *cube, int **map);
static void	ft_create_new_enemy(t_cube *cube, int **map, int x, int y);

int	update_loop(t_cube *cube)
{
	if (!cube->landing)
		return (1);
	if (!cube->mouse_drag)
		return (1);
	if (!cube->escape && !cube->lost)
		ft_update_image(cube);
	ft_pollution(cube, cube->map);
	return (1);
}

static void	ft_pollution(t_cube *cube, int **map)
{
	time_t	time;

	time = ft_time() - cube->start;
	if (time < SPAWN_TIME)
		return ;
	cube->start = ft_time();
	ft_propagate_pollution(cube, map);
	ft_convert_enemy(cube, map);
}

static void	ft_propagate_pollution(t_cube *cube, int **map)
{
	int		x;
	int		y;

	x = 0;
	while (x < cube->map_lenght)
	{
		y = 0;
		while (y < cube->map_width)
		{
			if (map[x][y] == ENEMY)
			{
				ft_create_new_enemy(cube, map, x - 1, y);
				ft_create_new_enemy(cube, map, x, y - 1);
				ft_create_new_enemy(cube, map, x + 1, y);
				ft_create_new_enemy(cube, map, x, y + 1);
			}
			y++;
		}
		x++;
	}
}

static void	ft_convert_enemy(t_cube *cube, int **map)
{
	int		x;
	int		y;
	bool	has_zeros;

	x = -1;
	has_zeros = 0;
	while (++x < cube->map_lenght)
	{
		y = 0;
		while (y < cube->map_width)
		{
			if (map[x][y] == NEW_ENEMY || map[x][y] == HURT_ENEMY)
				map[x][y] = ENEMY;
			if (map[x][y] == 0 && \
				(x != (int)cube->player.x || y != (int)cube->player.y))
				has_zeros = 1;
			y++;
		}
	}
	if (has_zeros)
		return ;
	cube->lost = 1;
	ft_create_image(cube);
	put_my_img_to_img(0, 0, cube->sprites[LOST], cube->img);
	ft_destroy_image(cube);
}

static void	ft_create_new_enemy(t_cube *cube, int **map, int x, int y)
{
	if (x < 0 || y < 0)
		return ;
	if ((map[x][y] == 0 || map[x][y] == OPENED_DOOR) \
		&& (x != (int)cube->player.x || y != (int)cube->player.y))
		map[x][y] = NEW_ENEMY;
	return ;
}
