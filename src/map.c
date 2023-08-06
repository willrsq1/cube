/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:58:38 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/06 11:58:23 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	**map_allocation(int fd, t_cube *cube);
static void	map_size(int *nb_of_lines, int *max_lenght, int fd, t_cube *cube);
static int	**address_allocation(int **map, int nb_of_lines, int max_lenght);
static void	fill_map(int fd, int **map, t_cube *cube);

int	**ft_map(char *path, t_cube *cube)
{
	int		**map;
	int		fd;

	cube->fd = -1;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror(path);
		exit(1);
	}
	cube->fd = fd;
	ft_textures_and_colors(cube, fd);
	map = map_allocation(fd, cube);
	cube->map = map;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror(path);
		ft_free_exit(cube);
	}
	cube->fd = fd;
	skip_elements(fd, cube);
	fill_map(fd, map, cube);
	close(fd);
	cube->fd = -1;
	return (map);
}

static int	**map_allocation(int fd, t_cube *cube)
{
	int		**map;
	int		nb_of_lines;
	int		max_lenght;

	nb_of_lines = 0;
	max_lenght = 0;
	map = NULL;
	map_size(&nb_of_lines, &max_lenght, fd, cube);
	cube->map_lenght = nb_of_lines;
	cube->map_width = max_lenght;
	map = address_allocation(map, nb_of_lines, max_lenght);
	if (!map)
	{
		write(2, "Error: Allocation of map.\n", 26);
		close(fd);
		exit(1);
	}
	return (map);
}

static void	map_size(int *nb_of_lines, int *max_lenght, int fd, t_cube *cube)
{
	char	*buff;
	int		y;

	while (1 && *nb_of_lines < INT_MAX)
	{
		y = 0;
		buff = get_next_line(fd);
		if (!buff)
			break ;
		while (buff[y] == ' ')
			y++;
		while (buff[y] && buff[y] != '\n')
		{
			if (!(buff[y] == 'N' || buff[y] == 'S' || buff[y] == 'E' || \
				buff[y] == 'W' || buff[y] == '0' || buff[y] == '1' || \
				buff[y] == ' ' || buff[y] == 'D'))
				ft_error("Unallowed character in map.", NULL, NULL, cube);
			y++;
		}
		if (y > *max_lenght)
			*max_lenght = y;
		*nb_of_lines += 1;
		free(buff);
	}
	close(fd);
	cube->fd = -1;
}

static int	**address_allocation(int **map, int nb_of_lines, int max_lenght)
{
	int		y;

	map = ft_calloc(sizeof(int *) * nb_of_lines + 5, 1);
	if (!map)
		return (NULL);
	y = -1;
	while (++y < nb_of_lines)
	{
		map[y] = ft_calloc(sizeof(int) * max_lenght + 5, 1);
		if (!map[y])
		{
			while (--y >= 0)
				free(map[y]);
			return (NULL);
		}
	}
	return (map);
}

static void	fill_map(int fd, int **map, t_cube *cube)
{
	char	*buff;
	int		x;
	int		y;
	bool	map_started;

	x = 0;
	map_started = 0;
	while (1 && x < INT_MAX)
	{
		y = 0;
		buff = get_next_line(fd);
		if (!buff)
			break ;
		while (buff[y] && buff[y] != '\n')
		{
			map_started = 1;
			map[x][y] = ft_atoi_cube(buff[y]);
			if (map[x][y] == PLAYER_POSITION)
				map[x][y] = (int)buff[y];
			y++;
		}
		if (y == 0 && map_started == 1)
			ft_error("Empty line in map.", NULL, NULL, cube);
		while (y <= cube->map_width)
			map[x][y++] = END;
		free(buff);
		x++;
	}
	cube->map_lenght = x;
}
