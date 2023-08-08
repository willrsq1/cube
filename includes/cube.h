/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:57:50 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/08 16:25:47 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "cube_defines.h"

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
	double		vector_x_start;
	double		vector_y_start;
	double		vector_x;
	double		vector_y;
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
	int			height;
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
void	fix_angle(double *angle);

void	ft_minimap(t_cube *cube);
char	**ft_split(char const *s, char c);
int		ft_get_color(int color, t_cube *cube, char *s);
void	ft_free_tab(char **tab);

void	print_door_message(t_cube *cube);
void	print_s(int x, int y, t_cube *cube, int color);
void	print_x(int x, int y, t_cube *cube, int color);

void	draw_pov_player(t_cube *cube, t_player *player, int color, int coef);
int		handle_mouse_move(int x, int y, t_cube *cube);
int		handle_mouse_click(int key, int x, int y, t_cube *cube);

void	ft_hooks_bonus(t_cube *cube);
void	ft_key_hook_bonus(int key, t_cube *cube);
void	ft_update_image_bonus(t_cube *cube);
void	ft_key_pressed(int key, t_cube *cube);
bool	ft_check_player_position(t_cube *cube);

#endif