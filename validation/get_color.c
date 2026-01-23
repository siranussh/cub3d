/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 18:38:27 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 20:55:50 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int double_arr_size(char **arr)
{
	int size;

	if (!arr)
		return (0);
	size = 0;
	while(arr[size])
		size++;
	return (size);
}

static int	is_only_digits(char *color_rgb)
{
	int	i;

	i = 0;
	while (ft_isspace(color_rgb[i]))
		i++;
	while (color_rgb[i])
	{
		if (color_rgb[i] && (color_rgb[i] < '0' || color_rgb[i] > '9'))
		{
			if (color_rgb[i] && ft_isspace(color_rgb[i]))
			{
				while (color_rgb[i] && ft_isspace(color_rgb[i]))
					i++;
				if (color_rgb[i] != '\0')
					return (0);
			}
			if (color_rgb[i] && (color_rgb[i] < 48 || color_rgb[i] > 57))
				return (0);
		}
		if (!color_rgb[i])
			return (1);
		i++;
	}
	return (1);
}

static int	check_rgb(char **rgb)
{
	int i;

	if (double_arr_size(rgb) < 3)
		return (0);
	i = 0;
	while (rgb[i])
	{
		if (!is_only_digits(rgb[i]))
			return (0);
		i++;
	}
	return (1);
}

void	get_color(t_map *m, char *map_line, char type)
{
	int	    r;
	int	    g;
	int	    b;
	char    **color_rgb;

	r = 0;
	g = 0;
	b = 0;
	color_rgb = ft_split(map_line, ',');
	if (check_rgb(color_rgb) == 0)
		free_map_print_error(m, "Error: Invalid rgb values\n");
	r = ft_atoi(color_rgb[0]);
	g = ft_atoi(color_rgb[1]);
	b = ft_atoi(color_rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		free_map_print_error(m, "Error: Invalid rgb values\n");
	if (type == 'F')
		m->floor_color = r * 65536 + g * 256 + b;
	if (type == 'C')
		m->ceiling_color = r * 65536 + g * 256 + b;
}

void	parse_colors(t_map *m, char *map_line)
{
	char	*trimmed;

	trimmed = ignore_spaces(map_line);
	if (ft_strncmp(trimmed, "C", 1) == 0)
	{
		if (m->ceiling_color != -1)
			free_map_print_error(m, "Error: Duplicate ceiling color\n");
		trimmed++;
		trimmed = ignore_spaces(trimmed);
		get_color(m, trimmed, 'C');
	}
	else if(ft_strncmp(trimmed, "F", 1) == 0)
	{
		if (m->floor_color != -1)
			free_map_print_error(m, "Error: Duplicate floor color\n");
		trimmed++;
		trimmed = ignore_spaces(trimmed);
		get_color(m, trimmed, 'F');
	}
	else
		free_map_print_error(m, "Error: Invalid map\n");
}
