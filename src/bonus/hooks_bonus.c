/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 03:03:59 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/08 04:03:03 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	ft_hooks_bonus(t_cube *cube)
{
	mlx_hook(cube->mlx_win, 6, 1L << 13, handle_mouse_move, cube);
	mlx_mouse_hook(cube->mlx_win, handle_mouse_click, cube);
}

void	weird_ft(t_cube *cube)
{
	size_t	i;
	int		height;

	height = cube->height;
	i = 135;
	while (i > 110)
	{
		if (i > 120)
			cube->height += i / 15 + 10;
		else
			cube->height += i % 110;
		ft_update_image(cube);
		i--;
	}
	while (cube->height > height)
	{
		cube->height -= 10;
		ft_update_image(cube);
	}
	cube->height = height;
}

void	ft_key_hook_bonus(int key, t_cube *cube)
{
	if (key == M_KEY)
		cube->minimap = (cube->minimap + 1) % 2;
	if (key == P_KEY)
		cube->mouse_drag = (cube->mouse_drag + 1) % 2;
	if (key == PLUS_KEY && cube->player.fov > 0)
		cube->player.fov -= 0.011;
	if (key == MINUS_KEY && cube->player.fov < PII)
		cube->player.fov += 0.011;
	if (key == SPACE_KEY)
		weird_ft(cube);
	if (key == B_KEY && cube->height < WIN_HEIGHT)
		cube->height += 10;
	if (key == N_KEY && cube->height > -WIN_HEIGHT)
		cube->height -= 10;
	ft_doors(key, cube);
}

void	ft_update_image_bonus(t_cube *cube)
{
	if (cube->door_message)
		print_door_message(cube);
	if (cube->minimap)
		ft_minimap(cube);
}

int	handle_mouse_move(int x, int y, t_cube *cube)
{
	if (!cube->mouse_drag)
		return (1);
	cube->mouse_drag = 0;
	if (x > cube->mouse_x)
		cube->player.direction -= (cube->mouse_x - x) * 0.003;
	if (x < cube->mouse_x)
		cube->player.direction += (x - cube->mouse_x) * 0.003;
	cube->mouse_x = x;
	cube->mouse_y = y;
	ft_update_image(cube);
	cube->mouse_drag = 1;
	return (1);
}

int	handle_mouse_click(int key, int x, int y, t_cube *cube)
{
	cube->mouse_x = x;
	cube->mouse_y = y;
	if (key)
		return (1);
	return (1);
}
