/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:09:06 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 12:45:43 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	texture_path_len(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			len++;
		i++;
	}
	return (len);
}

char	*get_texture_path(t_map *m, char *map)
{
	char	*path;
	int		texture_len;

	if (!map || !*map)
		return (NULL);
	texture_len = 0;
	while (ft_isspace(*map) == 1)
		map++;
	texture_len = texture_path_len(map);
	if (texture_len == 0)
		return (NULL);
	path = ft_strncpy(m->no_tx, map, texture_len);
	if (!path)
		return (NULL);
	return (path);
}

int	if_tx_path_valid(char *path)
{
	// int	i;

	// i = 0;
	if (!path)
		return (0);
	if (path[0] != '.' && path[1] != '/')
		return (0);
	if (!valid_path(path, ".xpm"))
		return (0);
	return (1);
}

void	init_tx_paths(t_map *m, char *line)
{
	if (ft_strcmp(line, "NO"))
	{
		m->no_tx = get_texture_path(m, line);
		if (!m->no_tx || !if_tx_path_valid(m->no_tx))
			return ;
	}
	else if(ft_strcmp(line, "EA"))
	{
		m->ea_tx = get_texture_path(m, line);
		if (!m->ea_tx)
			return ;
	}
	else if (ft_strcmp(line, "WE"))
	{
		m->we_tx = get_texture_path(m, line);
		if (!m->we_tx)
			return ;
	}
	else if(ft_strcmp(line, "SO"))
	{
		m->so_tx = get_texture_path(m, line);
		if (!m->so_tx)
			return ;
	}
}

