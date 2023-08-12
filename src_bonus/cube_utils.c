/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:57:56 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/12 18:40:07 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube_bonus.h"

static void	ft_free_textures(t_cube *cube);

int	ft_valid_pos_bonus(t_cube *cube, double x, double y)
{
	if (x < 0 || \
		y < 0 || \
		y > cube->map_width || \
		x > cube->map_lenght || \
		cube->map[(int)x][(int)y] == END || \
		cube->map[(int)x][(int)y] == WALL)
		return (WALL);
	if (cube->map[(int)x][(int)y] == CLOSED_DOOR)
		return (CLOSED_DOOR);
	if (cube->map[(int)x][(int)y] == OPENED_DOOR)
		return (OPENED_DOOR);
	if (cube->map[(int)x][(int)y] <= ENEMY && cube->animation)
	{
		cube->enemy = 1;
	}
	return (0);
}

void	ft_free_exit(t_cube *cube)
{
	int	i;

	i = -1;
	if (cube->map)
	{
		while (++i < cube->map_lenght)
			free(cube->map[i]);
		free(cube->map);
	}
	if (cube->fd != -1)
		close(cube->fd);
	if (cube->img && cube->img->img_ptr)
		mlx_destroy_image(cube->mlx, cube->img->img_ptr);
	if (cube->mlx_win)
		mlx_destroy_window(cube->mlx, cube->mlx_win);
	ft_free_textures(cube);
	if (cube->mlx)
		mlx_destroy_display(cube->mlx);
	if (cube->mlx)
		free(cube->mlx);
	exit(0);
}

static void	ft_free_textures(t_cube *cube)
{
	int	i;

	if (cube->text_north)
		free(cube->text_north);
	if (cube->text_south)
		free(cube->text_south);
	if (cube->text_west)
		free(cube->text_west);
	if (cube->text_east)
		free(cube->text_east);
	i = -1;
	while (cube->sprites[++i].img_ptr)
		mlx_destroy_image(cube->mlx, cube->sprites[i].img_ptr);
}

void	ft_error(char *s1, char *s2, char *s3, t_cube *cube)
{
	write(2, "error: ", 7);
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		free(s3);
	write(2, "\n", 1);
	ft_free_exit(cube);
}

bool	ft_check_player_position(t_cube *cube)
{
	cube->enemy = 0;
	if (ft_valid_pos_bonus(cube, cube->player.x, cube->player.y) > 0)
	{
		if (ft_valid_pos_bonus(cube, cube->player.prev_x, cube->player.y) <= 0)
			cube->player.x = cube->player.prev_x;
		else if (ft_valid_pos_bonus(cube, \
			cube->player.x, cube->player.prev_y) <= 0)
			cube->player.y = cube->player.prev_y;
		else
		{
			cube->player.x = cube->player.prev_x;
			cube->player.y = cube->player.prev_y;
			return (CANCEL_THE_MOVEMENT);
		}
	}
	if (cube->enemy)
	{
		if (ft_valid_pos_enemy(cube, cube->player.x, cube->player.y) <= ENEMY)
		{
			cube->player.x = cube->player.prev_x;
			cube->player.y = cube->player.prev_y;
			return (CANCEL_THE_MOVEMENT);
		}
	}
	return (POSITION_IS_GOOD);
}
