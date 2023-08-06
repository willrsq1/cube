/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:57:50 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 11:46:15 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx_linux/mlx.h"

# define PLAYER_POSITION -42
# define END -1
# define SPACE -2
# define FAIL -3
# define PI2 1.570796000000000081087137004942633211612701416015625
# define PI  3.141592999999999857863031138549558818340301513671875
# define PII 6.283184999999999575948095298372209072113037109375
# define PI3 4.7123889923095703125
# define FOV 1
# define WALL 1
# define RESOLUTION 0.0001
# define WIN_WIDTH 1300
# define WIN_HEIGHT 800
# define CEILING_COLOR 0x155202243
# define FLOOR_COLOR 0x208171147
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00
# define BLACK 0x000000
# define MAROON 0x800000
# define CYAN 0x00FFFF
# define BEACH_YELLOW 0xFFD700
# define PASTEL_PINK 0xFFB6C1
# define PASTEL_YELLOW 0xFFFF99
# define PASTEL_BLUE 0xADD8E6
# define PASTEL_GREEN 0x98FB98
# define PASTEL_PURPLE 0xE6E6FA
# define PASTEL_ORANGE 0xFFDAB9
# define PASTEL_MINT 0x98FF98
# define PASTEL_PEACH 0xFFDAB9
# define PASTEL_LAVENDER 0xE6E6FA
# define PASTEL_BEIGE 0xF5F5DC

# define CLOSED_DOOR 2
# define OPENED_DOOR -2

# define ESC_KEY 65307
# define UP_ARROW 65362
# define LEFT_ARROW 65361
# define DOWN_ARROW 65364
# define RIGHT_ARROW 65363
# define A_KEY 97
# define Z_KEY 122

typedef struct s_cube	t_cube;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		prev_x;
	double		prev_y;
	double		dist_x_start;
	double		dist_y_start;
	double		dist_x;
	double		dist_y;
	double		direction;
	int			color;
	t_img		*texture;
	t_cube		*cube;
	double		fov;
}	t_player;

typedef struct s_cube
{
	int			**map;
	int			fd;
	int			map_lenght;
	int			map_width;
	t_player	player;
	void		*mlx;
	void		*mlx_win;
	t_img		*img;
	char		*text_north;
	char		*text_south;
	char		*text_west;
	char		*text_east;
	int			ceiling_color;
	int			floor_color;
	bool		minimap;
}	t_cube;

void	ft_cube(char **argv);

int		**ft_map(char *path, t_cube *cube);

void	ft_free_exit(t_cube *cube);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi_cube(char c);

void	get_player_position(t_cube *cube);

void	launch_mlx(t_cube *cube);
void	launch_window(t_cube *cube);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

int		ft_close(t_cube *cube);
int		ft_key_hook(int key, t_cube *cube);

void	ft_draw(t_cube *cube);

void	ft_raycasting(t_cube *cube, t_player *player);

void	fix_angle(t_player *player);
double	ft_distance(double x, double y, double x0, double y0);

void	ft_error(char *s1, char *s2, char *s3, t_cube *cube);
int		ft_close(t_cube *cube);

int		ft_valid_pos(t_cube *cube, double x, double y);

void	ft_textures_and_colors(t_cube *cube, int fd);
void	skip_elements(int fd, t_cube *cube);

void	ft_doors(int key, t_cube *cube);

#endif