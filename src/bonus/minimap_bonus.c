/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:41:43 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/07 03:00:06 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	ft_draw_square(int size, int y, int x, t_cube *cube);
static void	ft_draw_player(int size, double y, double x, t_img *img);

void	ft_minimap(t_cube *cube)
{
	int		y;
	int		x;
	int		coef;

	y = 0;
	coef = WIN_WIDTH / 100;
	if (coef * cube->map_width > WIN_WIDTH)
		coef = WIN_HEIGHT / cube->map_width * 1.5;
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
	draw_pov_player(cube, &cube->player, NAVY_BLUE, coef);
	ft_draw_player(coef, cube->player.x, cube->player.y, cube->img);
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

static void	ft_draw_player(int size, double y, double x, t_img *img)
{
	int	i;
	int	m;

	m = 0;
	i = -2;
	while (++i < 4)
	{
		ft_pixel(img, x * size + m, y * size + m + i, RED);
		ft_pixel(img, x * size + m + 1, y * size + m + i, RED);
	}
	ft_pixel(img, x * size + m - 1, y * size - 1, RED);
	ft_pixel(img, x * size + m + 2, y * size - 1, RED);
	ft_pixel(img, x * size + m - 1, y * size, RED);
	ft_pixel(img, x * size + m + 2, y * size, RED);
	ft_pixel(img, x * size + m - 1, y * size + 1, RED);
	ft_pixel(img, x * size + m - 2, y * size + 1, RED);
	ft_pixel(img, x * size + m + 2, y * size + 1, RED);
	ft_pixel(img, x * size + m + 3, y * size + 1, RED);
	ft_pixel(img, x * size + m - 1, y * size + 2, RED);
	ft_pixel(img, x * size + m + 2, y * size + 2, RED);
}
