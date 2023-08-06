/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:57:45 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/05 23:25:00 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	fix_angle(t_player *player)
{
	if (player->direction >= PII)
		player->direction -= PII;
	if (player->direction <= 0)
		player->direction += PII;
}

double	ft_distance(double x, double y, double x0, double y0)
{
	double	dist;

	x = x0 - x;
	if (x < 0)
		x *= -1;
	y = y0 - y;
	if (y < 0)
		y *= -1;
	dist = sqrt(x * x + y * y);
	return (dist);
}
