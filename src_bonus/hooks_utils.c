/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:13:23 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/12 18:41:39 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube_bonus.h"

static void	ft_move_right(t_cube *cube);
static void	ft_move_left(t_cube *cube);
static void	esc_key_function(int key, t_cube *cube);

void	ft_key_pressed(int key, t_cube *cube)
{
	printf("%d\n", key);
	if (key == ESC_KEY || cube->escape)
		esc_key_function(key, cube);
	if (key == A_KEY)
		cube->player.angle -= 0.07;
	if (key == Z_KEY)
		cube->player.angle += 0.07;
	if (key == UP_ARROW)
	{
			cube->player.x += cos(cube->player.angle) / 10;
			cube->player.y += sin(cube->player.angle) / 10;
	}
	if (key == DOWN_ARROW)
	{
		cube->player.x -= cos(cube->player.angle) / 10;
		cube->player.y -= sin(cube->player.angle) / 10;
	}
	if (key == RIGHT_ARROW)
		ft_move_right(cube);
	if (key == LEFT_ARROW)
		ft_move_left(cube);
	if (key == P_KEY && cube->landing)
		cube->animation = (cube->animation + 1) % 2;
	ft_key_enemy(key, cube);
}

static void	pause_screen_image(int key, t_cube *cube)
{
	if (key == LEFT_ARROW)
	{
		cube->escape = PAUSE_LEFT;
		put_my_img_to_img(0, 0, cube->sprites[PAUSE_LEFT], cube->img);
	}
	else if (key == RIGHT_ARROW)
	{
		cube->escape = PAUSE_RIGHT;
		put_my_img_to_img(0, 0, cube->sprites[PAUSE_RIGHT], cube->img);
	}
}

static void	esc_key_function(int key, t_cube *cube)
{
	ft_create_image(cube);
	if (cube->escape)
	{
		if ((key == ENTER_KEY && cube->escape == PAUSE_RIGHT) || key == ESC_KEY)
			ft_free_exit(cube);
		else if (key == ENTER_KEY && cube->escape == PAUSE_LEFT)
		{
			cube->escape = 0;
			cube->start = ft_time();
			if (!cube->landing)
				put_my_img_to_img(0, 0, cube->sprites[LANDING], cube->img);
		}
		else if (key == LEFT_ARROW || key == RIGHT_ARROW)
			pause_screen_image(key, cube);
		else
			put_my_img_to_img(0, 0, cube->sprites[cube->escape], cube->img);
	}
	else
	{
		cube->escape = PAUSE_LEFT;
		put_my_img_to_img(0, 0, cube->sprites[PAUSE_LEFT], cube->img);
	}
	ft_destroy_image(cube);
}

static void	ft_move_right(t_cube *cube)
{
	if (cube->player.angle > 0 && cube->player.angle < PI)
	{
		cube->player.x -= cos(cube->player.angle + PI / 2) / 10;
		cube->player.y -= sin(cube->player.angle + PI / 2) / 10;
	}
	else
	{
		cube->player.x += cos(cube->player.angle - PI / 2) / 10;
		cube->player.y += sin(cube->player.angle - PI / 2) / 10;
	}
}

static void	ft_move_left(t_cube *cube)
{
	if (cube->player.angle > 0 && cube->player.angle < PI)
	{
		cube->player.x -= cos(cube->player.angle - PI / 2) / 10;
		cube->player.y -= sin(cube->player.angle - PI / 2) / 10;
	}
	else
	{
		cube->player.x += cos(cube->player.angle + PI / 2) / 10;
		cube->player.y += sin(cube->player.angle + PI / 2) / 10;
	}
}
