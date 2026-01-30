/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manipulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:58:26 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/30 18:20:14 by anavagya         ###   ########.fr       */
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
		ft_strlcpy(map_copy[i], m->map[i], m->longest_line + 1);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

char	**make_map_rect(t_map *m)
{
	int		i;
	int		j;
	int		row_len;
	char	**map_rect;

	if (!m || !m->original_map)
		return (NULL);
	m->longest_line = maps_longest_line(m->original_map);
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
		{
			while (i-- > 0)
				free(map_rect[i]);
			free(map_rect);
			return (NULL);
		}
		row_len = ft_strlen(m->original_map[i]);
		j = 0;
		while (j < m->longest_line)
		{
			if (j >= row_len || m->original_map[i][j] == ' ')
				map_rect[i][j] = '6';
			else
				map_rect[i][j] = m->original_map[i][j];
			j++;
		}
		map_rect[i][j] = '\0';
		if (!map_rect[i])
		{
			while (--i >= 0)
				free(map_rect[i]);
			free(map_rect);
		}
		i++;
	}
	map_rect[i] = NULL;
	return (map_rect);
}

