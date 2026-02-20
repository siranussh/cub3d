/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 13:53:19 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/20 13:09:43 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**copy_map(t_map *m)
{
	int		i;
	char	**map_copy;

	i = 0;
	map_copy = (char **)malloc(sizeof(char *) * (m->map_size + 1));
	if (!map_copy)
		return (NULL);
	while (i < m->map_size)
	{
		map_copy[i] = (char *)malloc(sizeof(char) * (m->longest_line + 1));
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
		}
		ft_strlcpy(map_copy[i], m->rect_map[i], m->longest_line + 1);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static void	free_map_rect(char **map_rect, int i)
{
	while (i-- > 0)
		free(map_rect[i]);
	free(map_rect);
}

static void	fill_map_row(char *dst, char *src, int longest_line)
{
	int	j;
	int	row_len;

	row_len = ft_strlen(src);
	j = 0;
	while (j < longest_line)
	{
		if (j >= row_len || src[j] == ' ')
			dst[j] = '6';
		else
			dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
}

char	**make_map_rect(t_map *m)
{
	int		i;
	char	**map_rect;

	if (!m || !m->map)
		return (NULL);
	m->longest_line = maps_longest_line(m->map);
	if (!m->longest_line)
		return (NULL);
	map_rect = (char **)malloc(sizeof(char *) * (m->map_size + 1));
	if (!map_rect)
		return (NULL);
	i = 0;
	while (i < m->map_size)
	{
		map_rect[i] = (char *)malloc(sizeof(char) * (m->longest_line + 1));
		if (!map_rect[i])
			return (free_map_rect(map_rect, i), NULL);
		fill_map_row(map_rect[i], m->map[i], m->longest_line);
		i++;
	}
	map_rect[i] = NULL;
	return (map_rect);
}
