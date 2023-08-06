/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:41:43 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 19:43:23 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	ft_draw_square(int size, int y, int x, t_cube *cube)
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
					ft_pixel(cube->img, x * size + i, y * size + j, CLOSED_DOOR_COLOR);
				else if (cube->map[y][x] == OPENED_DOOR)
					ft_pixel(cube->img, x * size + i, y * size + j, OPENED_DOOR_COLOR);
				else if ((cube->map[y][x] == WALL))
					ft_pixel(cube->img, x * size + i, y * size + j, BLACK);
				else
					ft_pixel(cube->img, x * size + i, y * size + j, GRAY);
			}
			i++;
		}
	}
}

void	ft_draw_player_body_and_head(int x, int y, int size, t_img *img)
{
	int	i;
	int	m;
	
	m = size / 2;
	i = -9;
	while (++i < 4)
	{
		ft_pixel(img, x * size + m, y * size + m + i, RED);
		ft_pixel(img, x * size + m + 1, y * size + m + i, RED);
	}
	ft_pixel(img, x * size + m - 1, y * size + m - 5, RED);
	ft_pixel(img, x * size + m - 2, y * size + m - 5, RED);
	ft_pixel(img, x * size + m + 2, y * size + m - 5, RED);
	ft_pixel(img, x * size + m + 3, y * size + m - 5, RED);
	ft_pixel(img, x * size + m - 1, y * size + m - 4, RED);
	ft_pixel(img, x * size + m + 2, y * size + m - 4, RED);
	ft_pixel(img, x * size + m - 1, y * size + m - 6, RED);
	ft_pixel(img, x * size + m + 2, y * size + m - 6, RED);
	ft_pixel(img, x * size + m - 1, y * size + m - 7, RED);
	ft_pixel(img, x * size + m + 2, y * size + m - 7, RED);
}

void	ft_draw_player(int size, int y, int x, t_img *img)
{
	int	m;
	int	i;
	int	j;

	m = size / 2;
	ft_draw_player_body_and_head(x, y, size, img);
	i = -1;
	j = 2;
	while (++i < 8)
	{
		ft_pixel(img, x * size + m / 2 + i, y * size + m - 1, RED);
		ft_pixel(img, x * size + m / 2 + i, y * size + m - 2, RED);
		if (j > -2)
		{
			ft_pixel(img, x * size + m / 2 + i, y * size + size - 2 + j, RED);
			ft_pixel(img, x * size + m / 2 + i, y * size + size - 3 + j, RED);
		}
		else
		{
			ft_pixel(img, x * size + m / 2 + i, y * size + size - 6 - j, RED);
			ft_pixel(img, x * size + m / 2 + i, y * size + size - 7 - j, RED);
		}
		j--;
	}
}

void	ft_minimap(t_cube *cube)
{
	int		y;
	int		x;
	int		coef;

	y = 0;
	coef = WIN_WIDTH / 100;
	if (coef * cube->map_lenght > WIN_HEIGHT / 2)
		coef = WIN_HEIGHT / cube->map_lenght / 5;
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
	ft_draw_player(coef, (int)cube->player.x, (int)cube->player.y, cube->img);
}