/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:57:24 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/03 20:30:19 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	print_map(int **map, int map_lenght)
{
	int		i;
	int		y;

	i = 0;
	while (i < map_lenght)
	{
		y = 0;
		while (map[i][y] != END)
		{
			if (map[i][y] == SPACE)
				printf(" ");
			else if (map[i][y] > 1)
				printf("%c", map[i][y]);
			else
				printf("%d", map[i][y]);
			y++;
		}
		printf("\n");
		i++;
	}
}

void	ft_cube(char **argv)
{
	t_cube	cube;

	cube.map = ft_map(argv[1], &cube.map_lenght);
	print_map(cube.map, cube.map_lenght);
	get_player_position(&cube);
	ft_exit(cube.map, cube.map_lenght, -1);
}
