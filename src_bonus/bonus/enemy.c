/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:24 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/10 22:46:00 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes_bonus/cube_bonus.h"

void	cc(int x_start, int y_start, int height, int width, int coef_h, int coef_w, t_img tex, t_img *img)
{
	int				i;
	int				y;
	unsigned int	pix;

	i = 0;
	while (i < height)
	{
		y = 0;
		while (y < width)
		{
			pix = get_pixel_img(tex, y / coef_h, i / coef_w);
			if (pix != 0xFFFFFF && pix != 0x000000)
				ft_pixel(img, x_start + y, y_start + i, pix);
			y++;
		}
		i++;
	}
}

int	truc(t_cube *cube)
{
	time_t	time;

	time = (ft_time() - cube->start) % 1000;
	if (time > 750)
		cube->id = CAT4;
	if (time > 500)
		cube->id = CAT3;
	if (time > 250)
		cube->id = CAT2;
	else
		cube->id = CAT1;
	usleep(100000);
	ft_update_image(cube);
	// cc(300, 300, 500, 500, 500 / cube->sprites[CAT1].img_height, 500 / cube->sprites[CAT1].img_width, cube->sprites[CAT1], cube->img);
	ft_destroy_image(cube);
	// usleep(100000);
	// // ft_update_image(cube);
	// cc(300, 300, 500, 500, 500 / cube->sprites[CAT2].img_height, 500 / cube->sprites[CAT2].img_width, cube->sprites[CAT2], cube->img);
	// ft_destroy_image(cube);
	// usleep(100000);
	// // ft_update_image(cube);
	// cc(300, 300, 500, 500, 500 / cube->sprites[CAT3].img_height, 500 / cube->sprites[CAT3].img_width, cube->sprites[CAT3], cube->img);
	// ft_destroy_image(cube);
	// usleep(100000);
	// // ft_update_image(cube);
	// cc(300, 300, 500, 500, 500 / cube->sprites[CAT4].img_height, 500 / cube->sprites[CAT4].img_width, cube->sprites[CAT4], cube->img);
	// ft_destroy_image(cube);
	// usleep(100000);
	
	return (1);
}

