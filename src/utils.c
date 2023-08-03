/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wruet-su <william.ruetsuquet@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:57:56 by wruet-su          #+#    #+#             */
/*   Updated: 2023/08/03 20:29:55 by wruet-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	ft_bzero(void *s, size_t n);

void	ft_exit(int **map, int map_lenght, int fd)
{
	int		i;

	i = -1;
	if (map)
	{
		while (++i < map_lenght)
			free(map[i]);
		free(map);
	}
	if (fd != -1)
		close(fd);
	exit(1);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

int	ft_atoi_cube(char c, char *s)
{
	if (c == ' ')
		return (SPACE);
	if (c == '0' || c == '1')
		return (c - 48);
	if (c == 'N' || \
		c == 'S' || \
		c == 'E' || \
		c == 'W')
		return (PLAYER_POSITION);
	write(2, "Error: The map has the char '", 29);
	write(2, &c, 1);
	write(2, "' in its file.\n", 15);
	free(s);
	return (FAIL);
}
