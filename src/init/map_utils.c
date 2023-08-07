/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:56:12 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/07 03:01:49 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static char	*ft_get_texture(char *texture, t_cube *cube, char *s);
static char	*check_error_element(char *s, t_cube *cube);
static int	ft_get_color(int color, t_cube *cube, char *s);

void	ft_textures_and_colors(t_cube *cube, int fd, char *s, int count)
{
	while (count != 6)
	{
		s = get_next_line(fd);
		if (!s && write(2, "Incomplete .cub file: Missing an identifier.\n", 45))
			ft_free_exit(cube);
		if (s[0] == 'N' && (s[1] == 'O' || s[1] == ' ') && ++count)
			cube->text_north = ft_get_texture(cube->text_north, cube, s);
		else if (s[0] == 'S' && (s[1] == 'O' || s[1] == ' ') && ++count)
			cube->text_south = ft_get_texture(cube->text_south, cube, s);
		else if (s[0] == 'W' && (s[1] == 'E' || s[1] == ' ') && ++count)
			cube->text_west = ft_get_texture(cube->text_west, cube, s);
		else if (s[0] == 'E' && (s[1] == 'A' || s[1] == ' ') && ++count)
			cube->text_east = ft_get_texture(cube->text_east, cube, s);
		else if (s[0] == 'C' && s[1] == ' ' && ++count)
			cube->ceiling_color = ft_get_color(cube->ceiling_color, cube, s);
		else if (s[0] == 'F' && s[1] == ' ' && ++count)
			cube->floor_color = ft_get_color(cube->floor_color, cube, s);
		else if (s[0] != '\n' && count)
			ft_error("Unallowed lign.", NULL, s, cube);
		free(s);
	}
}

static char	*check_error_element(char *s, t_cube *cube)
{
	int		i;
	char	*texture;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	if (!s[i] || i > 2)
		ft_error("A line is not formated properly.", NULL, s, cube);
	while (s[i] && s[i] == ' ')
		i++;
	if (!s[i] || s[i] == '\n')
		ft_error("An element doesn't contain a file.", NULL, s, cube);
	texture = ft_strdup(&s[i]);
	if (!texture)
	{
		free(s);
		ft_free_exit(cube);
	}
	return (texture);
}

static char	*ft_get_texture(char *texture, t_cube *cube, char *s)
{
	int	fd;

	if (texture)
		ft_error("The element ", " has already been defined.", s, cube);
	s[ft_strlen(s) - 1] = '\0';
	texture = check_error_element(s, cube);
	fd = open(texture, O_RDONLY);
	if (fd != -1)
		close(fd);
	if (fd == -1)
	{
		perror(texture);
		free(texture);
		free(s);
		ft_free_exit(cube);
	}
	texture[ft_strlen(texture) - 1] = '\0';
	return (texture);
}

static int	ft_get_color(int color, t_cube *cube, char *s)
{
	if (color != -1)
		ft_error("Multiple definition of colors.", NULL, s, cube);
	if (cube && s)
		return (WHITE);
	return (WHITE);
}

void	skip_elements(int fd, t_cube *cube)
{
	char	*s;
	int		count;

	count = 0;
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			ft_error("Incomplete .cub file.", NULL, s, cube);
		if (s[0] == 'N' || s[0] == 'S' || s[0] == 'E' || \
			s[0] == 'W' || s[0] == 'C' || s[0] == 'F')
			count++;
		free(s);
		if (count == 6)
			return ;
	}
}
