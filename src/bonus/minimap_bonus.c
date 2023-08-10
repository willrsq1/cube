/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:41:43 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/10 17:48:52 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	ft_draw_square(int size, int y, int x, t_cube *cube);

void	ft_minimap(t_cube *cube)
{
	int		y;
	int		x;
	int		coef;

	y = 0;
	coef = WIN_WIDTH / 100;
	if (coef * cube->map_width > WIN_WIDTH)
		coef = WIN_HEIGHT / cube->map_width * 2;
	while (y < cube->map_lenght)
	{
		x = 0;
		while (cube->map[y][x] != END)
		{
			ft_draw_square(coef, y, x, cube);
			x++;
		}
		y++;
	}
	draw_pov_player(cube, &cube->player, RED, coef);
	put_my_img_to_img((cube->player.y - 1) * coef, (cube->player.x - 1.5) * coef, cube->sprites[MINNIE], cube->img);
}

static void	ft_draw_square(int size, int y, int x, t_cube *cube)
{
	int	i;
	int	j;

	j = -1;
	while (++j <= size)
	{
		i = 0;
		while (i <= size)
		{
			if (i == 0 || j == 0 || i == size || j == size)
				ft_pixel(cube->img, x * size + i, y * size + j, DARK_GRAY);
			else
			{
				if (cube->map[y][x] == CLOSED_DOOR)
					ft_pixel(cube->img, x * size + i, y * size + j, CD_COLOR);
				else if (cube->map[y][x] == OPENED_DOOR)
					ft_pixel(cube->img, x * size + i, y * size + j, OP_COLOR);
				else if ((cube->map[y][x] == WALL))
					ft_pixel(cube->img, x * size + i, y * size + j, BLACK);
				else
					ft_pixel(cube->img, x * size + i, y * size + j, GRAY);
			}
			i++;
		}
	}
}
