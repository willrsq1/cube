/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:56:12 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 00:26:36 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static char	*ft_get_texture(char *texture, t_cube *cube, char *buff);
static int	check_error_element(char *buff, t_cube *cube);
static int	ft_get_color(t_cube *cube, char *buff);

void	ft_textures_and_colors(t_cube *cube, int fd)
{
	char	*buff;
	int		count;

	count = 0;
	while (1)
	{
		buff = get_next_line(fd);
		if (!buff && write(2, "Incomplete .cub file\n", 22))
			ft_free_exit(cube);
		if (buff[0] == 'N' && ++count)
			cube->text_north = ft_get_texture(cube->text_north, cube, buff);
		else if (buff[0] == 'S' && ++count)
			cube->text_south = ft_get_texture(cube->text_south, cube, buff);
		else if (buff[0] == 'W' && ++count)
			cube->text_west = ft_get_texture(cube->text_west, cube, buff);
		else if (buff[0] == 'E' && ++count)
			cube->text_east = ft_get_texture(cube->text_east, cube, buff);
		else if (buff[0] == 'C' && ++count)
			cube->ceiling_color = ft_get_color(cube, buff);
		else if (buff[0] == 'F' && ++count)
			cube->floor_color = ft_get_color(cube, buff);
		free(buff);
		if (count == 6)
			return ;
	}
}

static int	check_error_element(char *buff, t_cube *cube)
{
	int	i;

	i = 0;
	while (buff[i] && buff[i] != ' ')
		i++;
	if (!buff[i])
		ft_error("The element ", buff, " is not formated properly.", cube);
	while (buff[i] && buff[i] == ' ')
		i++;
	if (!buff[i] || buff[i] == '\n')
		ft_error("The element ", buff, " doesn't contain a file.", cube);
	return (i);
}

static char	*ft_get_texture(char *texture, t_cube *cube, char *buff)
{
	int	fd;
	int	i;

	if (texture)
		ft_error("The element ", buff, " has already been defined.", cube);
	buff[ft_strlen(buff) - 1] = '\0';
	i = check_error_element(buff, cube);
	texture = ft_strdup(&buff[i]);
	if (!texture)
	{
		free(buff);
		ft_free_exit(cube);
	}
	fd = open(texture, O_RDONLY);
	if (fd != 1)
		close(fd);
	if (fd == -1)
	{
		free(texture);
		free(buff);
		perror(buff);
		ft_free_exit(cube);
	}
	texture[ft_strlen(texture) - 1] = '\0';
	return (texture);
}

static int	ft_get_color(t_cube *cube, char *buff)
{
	if (cube && buff)
		return (WHITE);
	return (WHITE);
}

void	skip_elements(int fd, t_cube *cube)
{
	char	*buff;
	int		count;

	count = 0;
	while (1)
	{
		buff = get_next_line(fd);
		if (!buff)
			ft_error("Incomplete .cub file.", NULL, NULL, cube);
		if (buff[0] == 'N' || buff[0] == 'S' || buff[0] == 'E' || \
			buff[0] == 'W' || buff[0] == 'C' || buff[0] == 'F')
			count++;
		free(buff);
		if (count == 6)
			return ;
	}
}
