/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:57:56 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 13:23:49 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	ft_free_textures(t_cube *cube);

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
	if (cube->mlx)
		mlx_destroy_display(cube->mlx);
	if (cube->mlx)
		free(cube->mlx);
	ft_free_textures(cube);
	exit(0);
}

static void	ft_free_textures(t_cube *cube)
{
	if (cube->text_north)
		free(cube->text_north);
	if (cube->text_south)
		free(cube->text_south);
	if (cube->text_west)
		free(cube->text_west);
	if (cube->text_east)
		free(cube->text_east);
}

int	ft_valid_pos(t_cube *cube, double x, double y)
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
	return (0);
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

int	ft_atoi_cube(char c)
{
	if (c == ' ')
		return (1);
	if (c == '0' || c == '1')
		return (c - 48);
	if (c == 'N' || \
		c == 'S' || \
		c == 'E' || \
		c == 'W')
		return (c);
	if (c == 'D')
		return (CLOSED_DOOR);
	return (FAIL);
}
