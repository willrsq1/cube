/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 03:03:59 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/12 11:21:59 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cube_bonus.h"

void	ft_hooks_bonus(t_cube *cube)
{
	mlx_hook(cube->mlx_win, 6, 1L << 13, handle_mouse_move, cube);
	mlx_mouse_hook(cube->mlx_win, handle_mouse_click, cube);
}

void	ft_update_image_bonus(t_cube *cube)
{
	if (cube->door_message)
		print_door_message(cube);
	if (cube->minimap)
		ft_minimap(cube);
	if (cube->animation)
	{
		if (cube->weapon == SWORD)
		{
			if (!cube->attacking)
				put_my_img_to_img(WIN_WIDTH * 0.6, WIN_HEIGHT - 250, \
					cube->sprites[SWORD], cube->img);
			else
				put_my_img_to_img(WIN_WIDTH * 0.4, WIN_HEIGHT - 350, \
					cube->sprites[SWORD2], cube->img);
		}
		else if (cube->weapon == GUN)
		{
			if (!cube->attacking)
				put_my_img_to_img(WIN_WIDTH * 0.2, WIN_HEIGHT - 250, \
					cube->sprites[GUN], cube->img);
			else
				put_my_img_to_img(WIN_WIDTH * 0.4, WIN_HEIGHT - 350, \
					cube->sprites[GUN2], cube->img);
		}
	}
}

void	ft_key_hook_bonus(int key, t_cube *cube)
{
	if (key == M_KEY)
		cube->minimap = (cube->minimap + 1) % 2;
	if (key == U_KEY)
		cube->mouse_drag = (cube->mouse_drag + 1) % 2;
	if (key == PLUS_KEY && cube->player.fov > 0)
		cube->player.fov -= 0.011;
	if (key == MINUS_KEY && cube->player.fov < PII)
		cube->player.fov += 0.011;
	if (key == J_KEY)
		ft_jump(cube);
	if (key == B_KEY && cube->height < WIN_HEIGHT)
		cube->height += 10;
	if (key == N_KEY && cube->height > -WIN_HEIGHT)
		cube->height -= 10;
	if (key == R_KEY)
		cube->height = 1;
	ft_doors(key, cube);
}

int	handle_mouse_move(int x, int y, t_cube *cube)
{
	if (!cube->mouse_drag)
		return (1);
	cube->mouse_drag = 0;
	if (x > cube->mouse_x && x - cube->mouse_x > 10)
		cube->player.angle -= (cube->mouse_x - x) * 0.003;
	else if (x < cube->mouse_x && cube->mouse_x - x > 10)
		cube->player.angle += (x - cube->mouse_x) * 0.003;
	else
		return (cube->mouse_drag = 1, 1);
	cube->mouse_x = x;
	cube->mouse_y = y;
	cube->mouse_drag = 1;
	return (1);
}

int	handle_mouse_click(int key, int x, int y, t_cube *cube)
{
	cube->mouse_x = x;
	cube->mouse_y = y;
	if (cube->escape)
	{
		ft_create_image(cube);
		if (x < 520 && x > 250 && y < 550 && y > 410)
		{
			cube->escape = 0;
			cube->start = ft_time();
			if (!cube->landing)
			{
				put_my_img_to_img(0, 0, cube->sprites[LANDING], cube->img);
				ft_destroy_image(cube);
			}
		}
		if (x < 880 && x > 630 && y < 530 && y > 420)
			ft_free_exit(cube);
	}
	if (key)
		return (1);
	return (1);
}
