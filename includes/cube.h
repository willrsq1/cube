/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:57:50 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/07 03:45:04 by wruet-su         ###   ########.fr       */
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
# define CEILING_COLOR 0x00FFFF
# define FLOOR_COLOR 0xFFD700
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
# define GRAY 0xE0E0E0
# define DARK_GRAY 0xA0A0A0
# define PASTEL_LILAC   0xC8A2C8
# define PASTEL_SKY     0xB0E2FF
# define PASTEL_SALMON  0xFA8072
# define PASTEL_MAUVE   0xE0B0FF
# define PASTEL_SEAFOAM 0x7FFFD4
# define PASTEL_CORAL   0xFF6F61
# define PASTEL_APRICOT 0xFDD5B1
# define PASTEL_TURQUOISE 0xAFEEEE
# define DARK_RED       0x8B0000
# define NAVY_BLUE        0x000080
# define BURGUNDY       0x800000
# define MAROON         0x800000
# define CRIMSON        0xDC143C
# define BRICK_RED      0xB22222
# define FIREBRICK      0xB22222
# define WINE_RED       0x722F37
# define OXBLOOD_RED    0x800020
# define RUBY_RED       0x9B111E
# define GARNET         0x6A2323
# define SANGUINE       0x872019
# define MAHOGANY       0xC04000
# define CHERRY_RED     0xE34234
# define BARN_RED       0x7C0A02
# define CRANBERRY      0x9B1B30
# define CARMINE        0x960018
# define CHILI_RED      0xE23D28
# define ROSEWOOD       0x65000B
# define TOMATO_RED     0xFF6347
# define VERMILION      0xE34234

# define CLOSED_DOOR 2
# define OPENED_DOOR -2

# define CD_COLOR 0x98FF98
# define OP_COLOR 0xADD8E6

# define X 1
# define CANCEL_THE_MOVEMENT 1
# define POSITION_IS_GOOD 0
# define ESC_KEY 65307
# define UP_ARROW 65362
# define LEFT_ARROW 65361
# define DOWN_ARROW 65364
# define RIGHT_ARROW 65363
# define A_KEY 97
# define Z_KEY 122
# define M_KEY 109
# define P_KEY 112

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
	int			minimap;
	bool		door_message;
	int			mouse_x;
	int			mouse_y;
	bool		mouse_drag;
}	t_cube;

void	ft_cube(char **argv);

int		**ft_map(char *path, t_cube *cube);

void	ft_free_exit(t_cube *cube);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi_cube(char c);

void	get_player_position(t_cube *cube);

void	ft_update_image(t_cube *cube);
void	ft_pixel(t_img *img, int x, int y, int color);

int		ft_close(t_cube *cube);
int		ft_key_hook(int key, t_cube *cube);

void	ft_raycasting(t_cube *cube, t_player *player);

void	fix_angle(t_player *player);
double	ft_distance(double x, double y, double x0, double y0);

void	ft_error(char *s1, char *s2, char *s3, t_cube *cube);
int		ft_close(t_cube *cube);

int		ft_valid_pos(t_cube *cube, double x, double y);
void	print_map(int **map, int map_lenght, t_cube *cube);

void	ft_textures_and_colors(t_cube *cube, int fd, char *s, int count);
void	skip_elements(int fd, t_cube *cube);

void	ft_doors(int key, t_cube *cube);

void	ft_check_map_is_closed(t_cube *cube, int **map);
bool	ft_format(char *s);

void	print_door_message(t_cube *cube);

void	ft_minimap(t_cube *cube);

void	print_door_message(t_cube *cube);
void	print_s(int x, int y, t_cube *cube, int color);
void	print_x(int x, int y, t_cube *cube, int color);

void	draw_pov_player(t_cube *cube, t_player *player, int color, int coef);
int		handle_mouse_move(int x, int y, t_cube *cube);
int		handle_mouse_click(int key, int x, int y, t_cube *cube);

void	ft_hooks_bonus(t_cube *cube);
void	ft_key_hook_bonus(int key, t_cube *cube);
void	ft_update_image_bonus(t_cube *cube);
void	ft_background(t_cube *cube);
void	ft_key_pressed(int key, t_cube *cube);
bool	ft_check_player_position(t_cube *cube);

#endif