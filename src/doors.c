/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:43:57 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 11:45:49 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"
static double	ft_check_for_closed_door(t_cube *cube);
static double	ft_check_for_opened_door(t_cube *cube);

void	ft_doors(int key, t_cube *cube)
{
	double i;

	i = ft_check_for_closed_door(cube);
	if (i)
	{
		printf("PRESS 113 TO OPEN ! \n");
		if (key == 113)
			cube->map[(int)(cube->player.x + cos(cube->player.direction) * i)][(int)(cube->player.y + sin(cube->player.direction) * i)] = OPENED_DOOR;
	}
	i = ft_check_for_opened_door(cube);
	if (i)
	{
		printf("PRESS 115 TO CLOOOOOOOOOSE ! \n");
		if (key == 115)
			cube->map[(int)(cube->player.x + cos(cube->player.direction) * i)][(int)(cube->player.y + sin(cube->player.direction) * i)] = CLOSED_DOOR;
	}
}

static double	ft_check_for_closed_door(t_cube *cube)
{
	double	i;

	i = 0.01;
	while (i < 2)
	{
		if (ft_valid_pos(cube, cube->player.x + cos(cube->player.direction) * i, cube->player.y + sin(cube->player.direction) * i) == CLOSED_DOOR)
			return (i);
		i += 0.01;
	}
	return (0);
}

static double	ft_check_for_opened_door(t_cube *cube)
{
	double	i;

	i = 0.01;
	if (cube->map[(int)cube->player.x][(int)cube->player.y] == OPENED_DOOR)
		return (0);
	while (i < 2)
	{
		if (ft_valid_pos(cube, cube->player.x + cos(cube->player.direction) * i, cube->player.y + sin(cube->player.direction) * i) == OPENED_DOOR)
			return (i);
		i += 0.01;
	}
	return (0);
}
