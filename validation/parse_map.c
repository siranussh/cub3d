/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:10:13 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 20:57:04 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	parse_map(t_map *m, int fd, char *line)
{
	int		i;

	i = 0;
	if (!line || !*line)
	{
		close(fd);
		free(line);
		print_error("Error: Map file is empty.\n");
	}
	// if (*line == '\n')
	// {
	// 	close(fd);
	// 	print_error("Error: Invalid map format.\n");
	// }
    /*********************************************************/
	m->map_lines = ft_split(line, '\n');
	close(fd);
	free(line);
	while (m->map_lines[i])
	{
		printf("map_lines[%d] ===    %s\n", i, m->map_lines[i]);
		i++;
	}
	/**********************************************************/
	i = 0;
	while(i < 4)
	{
		parse_news(m, m->map_lines[i]);//parsing textures, if they are valid
		i++;
	}
	if (!m->no_tx || !m->ea_tx || !m->we_tx || !m->so_tx)
		free_map_print_error(m, "Error: Missing texture\n");
	while(i !=6)
	{
		parse_colors(m, m->map_lines[i]);
		i++;
	}
	if (m->floor_color == -1 || m->ceiling_color == -1)
		free_map_print_error(m, "Error: Missing floor or ceiling color\n");
}
