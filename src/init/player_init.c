/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:30:09 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/08 03:09:16 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	get_player_direction(t_cube *cube, char c);

void	get_player_position(t_cube *cube)
{
	int		x;
	int		y;

	x = 0;
	while (x < cube->map_lenght)
	{
		y = 0;
		while (cube->map[x][y] != END)
		{
			if (cube->map[x][y] > 31)
			{
				cube->player.x = x + 0.5;
				cube->player.y = y + 0.5;
				cube->player.cube = cube;
				cube->player.texture = NULL;
				get_player_direction(cube, cube->map[x][y]);
				return ;
			}
			y++;
		}
		x++;
	}
}

void	print_map(int **map, int map_lenght, t_cube *cube)
{
	int		i;
	int		y;
	int		letter_number;

	i = 0;
	letter_number = 0;
	while (i < map_lenght)
	{
		y = 0;
		while (map[i][y] != END)
		{
			if (map[i][y] > 31 && ++letter_number)
				printf("%c", map[i][y]);
			else
				printf("%d", map[i][y]);
			y++;
		}
		printf("\n");
		i++;
	}
	if (letter_number != 1)
		ft_error("Error with starting position", NULL, NULL, cube);
}

static void	get_player_direction(t_cube *cube, char c)
{
	cube->player.fov = FOV;
	if (c == 'N')
		cube->player.direction = PI;
	if (c == 'S')
		cube->player.direction = 0;
	if (c == 'E')
		cube->player.direction = PI2;
	if (c == 'W')
		cube->player.direction = PI3;
}
