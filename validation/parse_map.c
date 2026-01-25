/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:10:13 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/25 17:50:51 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	parse_params(t_map *m, char *map_line)
{
	char	*trimmed;

	trimmed = ignore_spaces(map_line);
	if (ft_strncmp(trimmed, "NO", 2) == 0)
		get_no_texture(m, trimmed);
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		get_ea_texture(m, trimmed);
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		get_we_texture(m, trimmed);
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		get_so_texture(m, trimmed);
	else if (ft_strncmp(trimmed, "C", 1) == 0)
		get_c_color(m, trimmed);
	else if (ft_strncmp(trimmed, "F", 1) == 0)
		get_f_color(m, trimmed);
	else
	{
		free_map(m);
		print_error("Error: Invalid map\n");
	}
}

void	parse_map(t_map *m, int fd, char *line)
{
	int		i;
	int		index;

	i = 0;
	index = find_map_start(line);
	m->param_line = ft_substr(line, 0, index - 1);
	m->map_line = ft_substr(line, index, ft_strlen(line));
	free(line);
	close(fd);
	m->params = ft_split(m->param_line, '\n');
	i = 0;
	while (m->params[i])
	{
		parse_params(m, m->params[i]);
		i++;
	}
	if (!m->no_tx || !m->ea_tx || !m->we_tx || !m->so_tx)
		free_map_print_error(m, "Error: Missing texture\n");
	if (m->floor_color == -1 || m->ceiling_color == -1)
		free_map_print_error(m, "Error: Missing floor or ceiling color\n");
	m->map = ft_split(m->map_line, '\n');
	if (!m->map || !*(m->map))
		free_map_print_error(m, "Error: Map doesn't exist\n");
}
