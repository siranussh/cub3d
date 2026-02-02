/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:36:58 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/25 17:51:39 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

char	*get_map_lines(int fd)
{
	char	*tmp;
	char	*line;

	tmp = NULL;
	line = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
		{
			get_next_line(-1);
			if (!tmp)
				break ;
			free(tmp);
			free(line);
			return ("\n");
		}
		if (!line)
			line = ft_gnl_strdup(tmp);
		else
			line = ft_gnl_strjoin(line, tmp);
		free(tmp);
	}
	return (line);
}

void	check_if_file_is_empty(char *line, t_map *m, int fd)
{
	if (!line || !*line)
	{
		close(fd);
		free(line);
		free_map_print_error(m, "Error: Map file is empty\n");
	}
	if (str_is_only_spaces(line) == 1)
	{
		close(fd);
		free(line);
		free_map_print_error(m, "Error: Map file is empty\n");
	}
}
