/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:10:13 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 14:52:35 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

void	parse_map(t_map *m, int fd, char *line)
{
	char	**map_lines;//for splitting
	int		i;
	char	*trimmed;

	(void)m;
	i = 0;
	if (!line || !*line)
	{
		close(fd);
		free(line);
		print_error("Error: Map file is empty.\n");
	}
	if (*line == '\n')
	{
		close(fd);
		print_error("Error: Invalid map format.\n");
	}
    ////////
	map_lines = ft_split(line, '\n');
    while (map_lines[i])
    {
        printf("map_lines[%d] ===    %s\n", i, map_lines[i]);
        i++;
    }
	i = 0;
	while(i < 4)
	{
		trimmed = ignore_spaces(map_lines[i]);
		//     "    ./textures/bluestone.xpm  "
		//     "./textures/bluestone.xpm  "
		//////
		if (ft_strncmp(trimmed, "NO", 2) == 0)
		{
			trimmed += 2;
			trimmed = ignore_spaces(trimmed);
			m->no_tx = get_texture_path(trimmed);
			if (!m->no_tx)
				return ;
			if (!if_tx_path_valid(m->no_tx))
				print_error("Error: Invalid NO texture\n");
		}
		else if(ft_strncmp(trimmed, "EA", 2) == 0)
		{
			trimmed += 2;
			trimmed = ignore_spaces(trimmed);
			m->ea_tx = get_texture_path(trimmed);
			if (!m->ea_tx)
				return ;
			if (!if_tx_path_valid(m->ea_tx))
				print_error("Error: Invalid EA texture\n");
		}
		else if (ft_strncmp(trimmed, "WE", 2) == 0)
		{
			trimmed += 2;
			trimmed = ignore_spaces(trimmed);
			m->we_tx = get_texture_path(trimmed);
			if (!m->we_tx)
				return ;
			if (!if_tx_path_valid(m->we_tx))
				print_error("Error: Invalid WE texture\n");
		}
		else if(ft_strncmp(trimmed, "SO", 2) == 0)
		{
			trimmed += 2;
			trimmed = ignore_spaces(trimmed);
			m->so_tx = get_texture_path(trimmed);
			if (!m->so_tx)
				return ;
			if (!if_tx_path_valid(m->so_tx))
				print_error("Error: Invalid SO texture\n");
		}
		i++;
	}
	if (!map_lines)
	{
		close(fd);
		free(line);
		free_map(m);
		print_error("Error: Invalid map format or malloc error.\n");
	}
}
