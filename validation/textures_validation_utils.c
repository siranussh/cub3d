/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_validation_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:43:37 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 17:43:39 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	texture_path_len(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	len = 0;
	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

char	*get_texture_path(char *map)
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
	path = (char *)malloc(texture_len + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, map, texture_len);
	if (!path)
		return (NULL);
	return (path);
}

int	if_tx_path_valid(char *path)
{
	// int	fd;

	if (!path)
		return (0);
	if (path[0] != '.' && path[1] != '/')
		return (0);
	if (!valid_path(path, ".xpm"))
		return (0);
	// fd = open(path, O_RDONLY);
	// if (fd < 0)
	// 	return (0);
	// close(fd);
	return (1);
}
