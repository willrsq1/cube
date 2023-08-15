/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_img_loop_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 05:40:06 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/15 09:00:22 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cube_bonus.h"

int	update_loop(t_cube *cube)
{
	if (!cube->welcome_window || cube->difficulty_window)
		return (1);
	if (!cube->escape && !cube->lost && !cube->help_menu && !cube->win)
	{
		ft_update_image(cube);
		if (cube->map_has_enemies)
			ft_pollution(cube, cube->map);
	}
	return (1);
}

void	ft_update_image(t_cube *cube)
{
	ft_create_image(cube);
	ft_raycasting(cube, &cube->player);
	minimap_weapons_door_message(cube);
	if (cube->level == LEVEL_2)
		put_my_img_to_img(WIN_WIDTH * 0.4, 0, cube->sprites[SUN], cube->img);
	ft_destroy_image(cube);
	ft_kill_count(cube);
}
