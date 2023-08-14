/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_launch_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:37:05 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/14 14:20:17 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cube_bonus.h"

static void	launch_assets_part2(t_cube *cube);

void	launch_assets(t_cube *cube)
{
	get_img(cube, &cube->sprites[MINNIE], "assets/minnie.xpm");
	get_img(cube, &cube->sprites[CAT1], "assets/cat/cat1.xpm");
	get_img(cube, &cube->sprites[CAT2], "assets/cat/cat2.xpm");
	get_img(cube, &cube->sprites[CAT3], "assets/cat/cat3.xpm");
	get_img(cube, &cube->sprites[CAT4], "assets/cat/cat4.xpm");
	get_img(cube, &cube->sprites[DOOR], "assets/cat/cat4.xpm");
	get_img(cube, &cube->sprites[BRICK], "assets/cat/cat4.xpm");
	get_img(cube, &cube->sprites[NORTH], cube->text_north);
	get_img(cube, &cube->sprites[SOUTH], cube->text_south);
	get_img(cube, &cube->sprites[WEST], cube->text_west);
	get_img(cube, &cube->sprites[EAST], cube->text_east);
	get_img(cube, &cube->sprites[CAT0], "assets/cat/cat_5.xpm");
	get_img(cube, &cube->sprites[CAT_HURT], "assets/cat/cat_6.xpm");
	get_img(cube, &cube->sprites[CAT_DEAD], "assets/cat/cat_7.xpm");
	get_img(cube, &cube->sprites[SWORD], "assets/cat/sword.xpm");
	get_img(cube, &cube->sprites[SWORD2], "assets/cat/sword2.xpm");
	get_img(cube, &cube->sprites[GUN], "assets/cat/gun.xpm");
	get_img(cube, &cube->sprites[GUN2], "assets/cat/gun2.xpm");
	get_img(cube, &cube->sprites[LANDING], "assets/cat/landing.xpm");
	get_img(cube, &cube->sprites[PAUSE_LEFT], "assets/cat/pause_left.xpm");
	get_img(cube, &cube->sprites[PAUSE_RIGHT], "assets/cat/pause_right.xpm");
	get_img(cube, &cube->sprites[LOST], "assets/cat/lost.xpm");
	get_img(cube, &cube->sprites[HELP], "assets/cat/help.xpm");
	get_img(cube, &cube->sprites[WIN], "assets/cat/victory.xpm");
	launch_assets_part2(cube);
}

static void	launch_assets_part2(t_cube *cube)
{
	get_img(cube, &cube->sprites[TOMB], "assets/cat/tomb.xpm");
	get_img(cube, &cube->sprites[MINI_HURT], "assets/cat/cat_hurt.xpm");
	get_img(cube, &cube->sprites[EASY], \
		"assets/cat/difficulty_easy.xpm");
	get_img(cube, &cube->sprites[HARD], \
		"assets/cat/difficulty_hard.xpm");
	get_img(cube, &cube->sprites[IMPOSSIBLE], \
		"assets/cat/difficulty_impossible.xpm");
	get_img(cube, &cube->sprites[LEVEL_1], "assets/cat/level1.xpm");
	get_img(cube, &cube->sprites[LEVEL_2], "assets/cat/level2.xpm");
	get_img(cube, &cube->sprites[LEVEL_3], "assets/cat/level3.xpm");
	get_img(cube, &cube->sprites[LEVEL_4], "assets/cat/level4.xpm");
	get_img(cube, &cube->sprites[LEVEL_5], "assets/cat/level5.xpm");
	get_img(cube, &cube->sprites[LEVEL_6], "assets/cat/level6.xpm");
	get_img(cube, &cube->sprites[LEVEL_7], "assets/cat/level7.xpm");
	get_img(cube, &cube->sprites[LEVEL_8], "assets/cat/level8.xpm");
	get_img(cube, &cube->sprites[FINAL_WIN], "assets/cat/final_victory.xpm");
}
