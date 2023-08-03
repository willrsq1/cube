/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:30:09 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/03 21:11:13 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	get_player_direction(t_cube *cube, char c);

void	get_player_position(t_cube *cube)
{
	int		x;
	int		y;

	x = 0;
	while (x < cube->map_lenght)
	{
		y = 0;
		while (cube->map[x][y])
		{
			if (cube->map[x][y] > 1)
			{
				cube->player.x = x;
				cube->player.y = y;
				get_player_direction(cube, cube->map[x][y]);
				return ;
			}
			y++;
		}
		x++;
	}
}

static void	get_player_direction(t_cube *cube, char c)
{
	cube->player.fov = FOV;
	if (c == 'N')
		cube->player.direction = PI2;
	if (c == 'S')
		cube->player.direction = PI3;
	if (c == 'E')
		cube->player.direction = 0;
	if (c == 'W')
		cube->player.direction = PI;
}
