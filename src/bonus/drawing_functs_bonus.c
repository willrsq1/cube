/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_functs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:32:36 by marvin            #+#    #+#             */
/*   Updated: 2023/08/07 03:00:02 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

typedef struct s_draw
{
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					err;
	int					e2;
}			t_draw;

static void	ft_do_draw_loop(t_img *img, t_draw plot, int color);
static void	draw(t_draw plot, int color, t_img *img);

void	draw_pov_player(t_cube *cube, t_player *player, int color, int coef)
{
	double	angle_save;
	t_draw	plot;
	int		a;

	fix_angle(player);
	angle_save = player->direction;
	a = 0;
	player->color = BLUE;
	player->direction -= player->fov * 0.92;
	fix_angle(player);
	plot.x0 = player->x * coef;
	plot.y0 = player->y * coef;
	while (a <= WIN_WIDTH)
	{
		plot.x1 = plot.x0 + coef * cos(player->direction);
		plot.y1 = plot.y0 + coef * sin(player->direction);
		draw(plot, color, cube->img);
		player->direction += player->fov / WIN_WIDTH * 1.8;
		fix_angle(player);
		a++;
	}
	player->direction = angle_save;
}

static void	draw(t_draw plot, int color, t_img *img)
{
	plot.dx = abs(plot.x1 - plot.x0);
	plot.dy = -abs(plot.y1 - plot.y0);
	if (plot.x0 < plot.x1)
		plot.sx = 1;
	else
		plot.sx = -1;
	if (plot.y0 < plot.y1)
		plot.sy = 1;
	else
		plot.sy = -1;
	plot.err = plot.dx + plot.dy;
	ft_do_draw_loop(img, plot, color);
}

static void	ft_do_draw_loop(t_img *img, t_draw plot, int color)
{
	while (1)
	{
		ft_pixel(img, plot.y0, plot.x0, color);
		if (plot.x0 == plot.x1 && plot.y0 == plot.y1)
			break ;
		plot.e2 = 2 * plot.err;
		if (plot.e2 >= plot.dy)
		{
			plot.err = plot.dy + plot.err;
			plot.x0 += plot.sx;
		}
		if (plot.e2 <= plot.dx)
		{
			plot.err += plot.dx;
			plot.y0 += plot.sy;
		}
	}
}
