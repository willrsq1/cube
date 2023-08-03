/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:58:38 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/03 20:30:30 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static int	**map_allocation(int fd, int *map_lenght);
static void	map_size(int *nb_of_lines, int *max_lenght, int fd);
static int	**address_allocation(int **map, int nb_of_lines, int max_lenght);
static void	fill_map(int fd, int **map, int *map_lenght);

int	**ft_map(char *path, int *map_lenght)
{
	int		**map;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Bad open: ", 10);
		perror(path);
		exit(1);
	}
	map = map_allocation(fd, map_lenght);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror(path);
		ft_exit(map, *map_lenght, -1);
	}
	fill_map(fd, map, map_lenght);
	return (map);
}

static int	**map_allocation(int fd, int *map_lenght)
{
	int		**map;
	int		nb_of_lines;
	int		max_lenght;

	nb_of_lines = 0;
	max_lenght = 0;
	map = NULL;
	map_size(&nb_of_lines, &max_lenght, fd);
	*map_lenght = nb_of_lines;
	map = address_allocation(map, nb_of_lines, max_lenght);
	if (!map)
	{
		write(2, "Error: Allocation of map.\n", 26);
		close(fd);
		exit(1);
	}
	return (map);
}

static void	map_size(int *nb_of_lines, int *max_lenght, int fd)
{
	char	*buff;
	int		y;

	while (1 && *nb_of_lines < INT_MAX)
	{
		y = 0;
		buff = get_next_line(fd);
		if (!buff)
			break ;
		while (buff[y])
			y++;
		if (y > *max_lenght)
			*max_lenght = y;
		*nb_of_lines += 1;
		free(buff);
	}
	close(fd);
}

static int	**address_allocation(int **map, int nb_of_lines, int max_lenght)
{
	int		y;

	map = ft_calloc(sizeof(int *) * nb_of_lines + 1, 1);
	if (!map)
		return (NULL);
	y = -1;
	while (++y < nb_of_lines)
	{
		map[y] = ft_calloc(sizeof(int) * max_lenght + 1, 1);
		if (!map[y])
		{
			while (--y >= 0)
				free(map[y]);
			return (NULL);
		}
	}
	return (map);
}

static void	fill_map(int fd, int **map, int *map_lenght)
{
	char	*buff;
	int		x;
	int		y;

	x = 0;
	while (1 && x < INT_MAX)
	{
		y = 0;
		buff = get_next_line(fd);
		if (!buff)
			break ;
		while (buff[y] && buff[y] != '\n')
		{
			map[x][y] = ft_atoi_cube(buff[y], buff);
			if (map[x][y] == PLAYER_POSITION)
				map[x][y] = buff[y];
			if (map[x][y] == FAIL)
				ft_exit(map, *map_lenght, fd);
			y++;
		}
		map[x][y] = END;
		free(buff);
		x++;
	}
	close(fd);
}
