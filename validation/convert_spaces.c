/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:44:19 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/05 15:44:29 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	mark_outside_spaces(char **copy, t_map *m, int y, int x)
{
	if (y < 0 || x < 0 || y >= m->map_size || x >= m->longest_line)
		return ;
	if (copy[y][x] != '6' && copy[y][x] != ' ' && copy[y][x] != '\t')
		return ;
	copy[y][x] = 'V';
	mark_outside_spaces(copy, m, y - 1, x);
	mark_outside_spaces(copy, m, y + 1, x);
	mark_outside_spaces(copy, m, y, x - 1);
	mark_outside_spaces(copy, m, y, x + 1);
}

void	convert_enclosed_spaces(t_map *m)
{
	int		i;
	int		j;
	char	**copy;

	if (!m || !m->rect_map)
		return ;
	copy = (char **)malloc(sizeof(char *) * (m->map_size + 1));
	if (!copy)
		return ;
	i = 0;
	while (i < m->map_size)
	{
		copy[i] = (char *)malloc(sizeof(char) * (m->longest_line + 1));
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return ;
		}
		ft_strlcpy(copy[i], m->rect_map[i], m->longest_line + 1);
		i++;
	}
	copy[i] = NULL;
	i = 0;
	while (i < m->map_size)
	{
		if (copy[i][0] == '6' || copy[i][0] == ' ' || copy[i][0] == '\t')
			mark_outside_spaces(copy, m, i, 0);
		if (copy[i][m->longest_line - 1] == '6'
			|| copy[i][m->longest_line - 1] == ' '
			|| copy[i][m->longest_line - 1] == '\t')
			mark_outside_spaces(copy, m, i, m->longest_line - 1);
		i++;
	}
	j = 0;
	while (j < m->longest_line)
	{
		if (copy[0][j] == '6' || copy[0][j] == ' ' || copy[0][j] == '\t')
			mark_outside_spaces(copy, m, 0, j);
		if (copy[m->map_size - 1][j] == '6' || copy[m->map_size - 1][j] == ' '
			|| copy[m->map_size - 1][j] == '\t')
			mark_outside_spaces(copy, m, m->map_size - 1, j);
		j++;
	}
	i = 0;
	while (i < m->map_size)
	{
		j = 0;
		while (j < m->longest_line)
		{
			if ((m->rect_map[i][j] == '6' || m->rect_map[i][j] == ' ' ||
				m->rect_map[i][j] == '\t') && copy[i][j] != 'V')
				m->rect_map[i][j] = '0';
			j++;
		}
		i++;
	}
	ft_free(copy);
}
