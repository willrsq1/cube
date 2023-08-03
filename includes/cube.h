/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:57:50 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/03 21:11:02 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define PLAYER_POSITION -42
# define END -1
# define SPACE -2
# define FAIL -3
# define PI2 1.570796000000000081087137004942633211612701416015625
# define PI  3.141592999999999857863031138549558818340301513671875
# define PII 6.283184999999999575948095298372209072113037109375
# define PI3 4.7123889923095703125
# define FOV 0.66

typedef struct s_player
{
	double		x;
	double		y;
	double		direction;
	double		fov;
}	t_player;

typedef struct s_cube
{
	int			**map;
	int			map_lenght;
	t_player	player;
}	t_cube;

void	ft_cube(char **argv);

int		**ft_map(char *path, int *map_lenght);

void	ft_exit(int	**map, int map_lenght, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi_cube(char c, char *s);

void	get_player_position(t_cube *cube);

#endif