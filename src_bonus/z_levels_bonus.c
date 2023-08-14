/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_levels_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 09:16:05 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/14 14:21:15 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube_bonus.h"

void	ft_difficulty(int key, t_cube *cube)
{
	ft_create_image(cube);
	if (key == ENTER_KEY && \
		(cube->difficulty == EASY || \
		cube->difficulty == HARD || \
		cube->difficulty == IMPOSSIBLE))
		ft_landing_image(cube);
	else if (cube->difficulty == EASY && key == DOWN_ARROW)
	{
		cube->difficulty = HARD;
		put_my_img_to_img(0, 0, cube->sprites[cube->difficulty], cube->img);
	}
	else if (cube->difficulty == HARD && key == DOWN_ARROW)
	{
		cube->difficulty = IMPOSSIBLE;
		put_my_img_to_img(0, 0, cube->sprites[cube->difficulty], cube->img);
	}
	else if (cube->difficulty == HARD && key == UP_ARROW)
	{
		cube->difficulty = EASY;
		put_my_img_to_img(0, 0, cube->sprites[cube->difficulty], cube->img);
	}
	else if (cube->difficulty == IMPOSSIBLE && key == UP_ARROW)
	{
		cube->difficulty = HARD;
		put_my_img_to_img(0, 0, cube->sprites[cube->difficulty], cube->img);
	}
	else
		put_my_img_to_img(0, 0, cube->sprites[cube->difficulty], cube->img);
	ft_destroy_image(cube);
}

void	ft_landing_image(t_cube *cube)
{
	cube->welcome_window = 0;
	if (cube->level == 0 && !cube->difficulty_window)
		put_my_img_to_img(0, 0, cube->sprites[LANDING], cube->img);
	else if (cube->level == LEVEL_1)
		put_my_img_to_img(0, 0, cube->sprites[LEVEL_1], cube->img);
	if (cube->level == LEVEL_2)
		put_my_img_to_img(0, 0, cube->sprites[LEVEL_2], cube->img);
	if (cube->level == LEVEL_3)
		put_my_img_to_img(0, 0, cube->sprites[LEVEL_3], cube->img);
	if (cube->level == LEVEL_4)
		put_my_img_to_img(0, 0, cube->sprites[LEVEL_4], cube->img);
	if (cube->level == LEVEL_5)
		put_my_img_to_img(0, 0, cube->sprites[LEVEL_5], cube->img);
}

void	ft_levels(t_cube *cube)
{
	char	*s[2];

	if (cube->level == LEVEL_1)
		s[1] = "maps/level_2.cub";
	if ((cube->difficulty == EASY && cube->level == LEVEL_1) || \
		(cube->difficulty == HARD && cube->level == LEVEL_4))
	{
		cube->win = 1;
		cube->game_was_won = 1;
		ft_create_image(cube);
		put_my_img_to_img(0, 0, cube->sprites[FINAL_WIN], cube->img);
		ft_destroy_image(cube);
		return ;
	}
	if (cube->level == LEVEL_2)
		s[1] = "maps/level_3.cub";
	if (cube->level == LEVEL_3)
		s[1] = "maps/level_4.cub";
	if (cube->level == LEVEL_4)
		s[1] = "maps/level_5.cub";
	cube->win = 0;
	cube->level += 1;
	ft_free(cube);
	ft_cube(s, cube->level, cube->difficulty);
}
