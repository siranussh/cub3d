/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:10:13 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/25 17:12:57 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	parse_map(t_map *m, int fd, char *line)
{
	int		i;
	int		index;

	i = 0;
	index = 0;
	index = find_map_start(line);
	m->param_line = ft_substr(line, 0, index - 1);
	m->map_line = ft_substr(line, index, ft_strlen(line));
	free(line);
	close(fd);
	m->params = ft_split(m->param_line, '\n');
    /*********************ptint_the_map************************/
	while (m->params[i])
	{
		printf("params[%d] ===    %s\n", i, m->params[i]);
		i++;
	}
	/**********************************************************/
	i = 0;
	while (m->params[i])
	{
		
		i++;
	}
	if (!m->no_tx || !m->ea_tx || !m->we_tx || !m->so_tx)
		free_map_print_error(m, "Error: Missing texture\n");
	if (m->floor_color == -1 || m->ceiling_color == -1)
		free_map_print_error(m, "Error: Missing floor or ceiling color\n");
	/**********************************************************/

	// i = 0;
	// while(i < 4)
	// {
	// 	parse_news(m, m->params[i]);//parsing textures, if they are valid
	// 	i++;
	// }
	// if (!m->no_tx || !m->ea_tx || !m->we_tx || !m->so_tx)
	// 	free_map_print_error(m, "Error: Missing texture\n");
	// while(i != 6)
	// {
	// 	parse_colors(m, m->params[i]);
	// 	i++;
	// }
	// if (m->floor_color == -1 || m->ceiling_color == -1)
	// 	free_map_print_error(m, "Error: Missing floor or ceiling color\n");
	
	// filling m->map
	m->map = ft_split(m->map_line, '\n');
}
