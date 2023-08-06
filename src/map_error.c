/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 13:36:13 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 16:37:45 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static bool	ft_check_vertically(int x, int y, int **map, int max)
{
	int	z;

	z = x;
	while (z >= 0)
	{
		if (map[z][y] == WALL)
			break ;
		if (map[z][y] == END)
			return (1);
		z--;
	}
	if (z == -1)
		return (1);
	z = x;
	while (z < max)
	{
		if (map[z][y] == WALL)
			break ;
		if (map[z][y] == END)
			return (1);
		z++;
	}
	if (z == max)
		return (1);
	return (0);
}

static bool	ft_check_horizontally(int x, int y, int **map, int max)
{
	int	z;

	z = y;
	while (z >= 0)
	{
		if (map[x][z] == WALL)
			break ;
		if (map[x][z] == END)
			return (1);
		z--;
	}
	if (z == -1)
		return (1);
	z = y;
	while (z < max)
	{
		if (map[x][z] == WALL)
			break ;
		if (map[x][z] == END)
			return (1);
		z++;
	}
	if (z == max)
		return (1);
	return (0);
}

void	ft_check_map_is_closed(t_cube *cube, int **map)
{
	int	x;
	int	y;

	x = 0;
	while (x < cube->map_lenght)
	{
		y = 0;
		while (y < cube->map_width)
		{
			if (map[x][y] == 0 || map[x][y] == CLOSED_DOOR)
			{
				if (ft_check_vertically(x, y, map, cube->map_lenght) == 1)
					ft_error("Map unclosed.", NULL, NULL, cube);
				if (ft_check_horizontally(x, y, map, cube->map_width) == 1)
					ft_error("Map unclosed.", NULL, NULL, cube);
			}
			y++;
		}
		x++;
	}
}

bool	ft_format(char *s)
{
	int	i;
	
	i = 0;
	if (!s)
		return (1);
	while (s[i])
		i++;
	if (i < 4)
		return (1);
	if (s[i - 1] == 'b' && s[i - 2] == 'u' && \
		s[i - 3] == 'c' && s[i - 4] == '.')
		return (0);
	return (1);
}
