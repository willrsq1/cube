/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:57:24 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 10:03:16 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	ft_background(t_cube *cube);
static void	print_map(int **map, int map_lenght, t_cube *cube);

void	ft_check_map_is_closed(t_cube *cube, int **map)
{
	int	y;

	y = 0;
	while (map[0][y] != END)
	{
		if (map[0][y] != 1)
			ft_error("Map unclosed at line 0.", NULL, NULL, cube);
		y++;
	}
	y = 0;
	while (map[cube->map_lenght - 1][y] != END)
	{
		if (map[cube->map_lenght - 1][y] != 1)
		{
			ft_error("Map unclosed at last line.", NULL, NULL, cube);
		}
		y++;
	}
}

void	ft_cube(char **argv)
{
	t_cube	cube;
	t_img	img;

	ft_bzero(&cube, sizeof(t_cube));
	ft_bzero(&img, sizeof(t_img));
	cube.ceiling_color = -1;
	cube.floor_color = -1;
	cube.map = ft_map(argv[1], &cube);
	print_map(cube.map, cube.map_lenght, &cube);
	ft_check_map_is_closed(&cube, cube.map);
	get_player_position(&cube);
	cube.img = &img;
	launch_mlx(&cube);
	launch_window(&cube);
	ft_free_exit(&cube);
}

void	ft_draw(t_cube *cube)
{
	ft_background(cube);
	cube->player.dist_x = cos(cube->player.direction) * 0.1;
	cube->player.dist_y = sin(cube->player.direction) * 0.1;
	ft_raycasting(cube, &cube->player);
}

static void	ft_background(t_cube *cube)
{
	int	i;
	int	y;

	i = 0;
	while (++i < WIN_HEIGHT / 2)
	{
		y = 0;
		while (++y < WIN_WIDTH)
			my_mlx_pixel_put(cube->img, y, i, CYAN);
	}
	while (i < WIN_HEIGHT)
	{
		y = 0;
		while (++y < WIN_WIDTH)
			my_mlx_pixel_put(cube->img, y, i, BEACH_YELLOW);
		i++;
	}
}

static void	print_map(int **map, int map_lenght, t_cube *cube)
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
			if (map[i][y] == SPACE)
				printf(" ");
			else if (map[i][y] > 31 && ++letter_number)
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
