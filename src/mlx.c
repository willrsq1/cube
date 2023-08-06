/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:13:23 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 09:45:18 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	launch_mlx(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
	{
		perror("at mlx_init in launch_mlx");
		ft_free_exit(cube);
	}
	cube->mlx_win = mlx_new_window(cube->mlx, WIN_WIDTH, WIN_HEIGHT, "Cube");
	if (!cube->mlx_win)
	{
		perror("at mlx_new_window in launch_mlx");
		ft_free_exit(cube);
	}
	cube->img->img_ptr = mlx_new_image(cube->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cube->img->img_ptr)
	{
		perror("at mlx_new_image in launch_mlx");
		ft_free_exit(cube);
	}
	cube->img->addr = mlx_get_data_addr(cube->img->img_ptr, &cube->img->bpp, \
		&cube->img->size_line, &cube->img->endian);
	if (!cube->img->addr)
	{
		perror("at mlx_new_image in launch_mlx");
		ft_free_exit(cube);
	}
}

void	launch_window(t_cube *cube)
{
	ft_draw(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->img->img_ptr, 0, 0);
	mlx_destroy_image(cube->mlx, cube->img->img_ptr);
	cube->img->img_ptr = NULL;
	mlx_hook(cube->mlx_win, 2, 1L << 0, ft_key_hook, cube);
	mlx_hook(cube->mlx_win, 17, 1L << 17, ft_close, cube);
	mlx_loop(cube->mlx);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && y <= WIN_HEIGHT && x <= WIN_WIDTH)
	{
		dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	ft_close(t_cube *cube)
{
	ft_free_exit(cube);
	return (1);
}
