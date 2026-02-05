/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:58:09 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/04 14:05:28 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	int	i;

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

static int	count_commas(char *line)
{
	int	i;
	int	count;

	if (!line)
		return (-1);
	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	get_color(t_game *game, char *map_line, char type)
{
	int		r;
	int		g;
	int		b;
	char	**color_rgb;

	r = 0;
	g = 0;
	b = 0;
	if (count_commas(map_line) != 2)
		free_and_print_error(game, "Error: Invalid rgb values\n");
	color_rgb = ft_split(map_line, ',');
	if (check_rgb(color_rgb) == 0)
	{
		ft_free(color_rgb);
		free_and_print_error(game, "Error: Invalid rgb values\n");
	}
	if (double_arr_size(color_rgb) != 3)
	{
		ft_free(color_rgb);
		free_and_print_error(game, "Error: Invalid rgb values\n");
	}
	r	 = ft_atoi(color_rgb[0]);
	g = ft_atoi(color_rgb[1]);
	b = ft_atoi(color_rgb[2]);
	ft_free(color_rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		free_and_print_error(game, "Error: Invalid rgb values\n");
	if (type == 'F')
		game->map->floor_color = r * 65536 + g * 256 + b;
	if (type == 'C')
		game->map->ceiling_color = r * 65536 + g * 256 + b;
}

void	get_c_color(t_game *game, char *map_line)
{
	if (game->map->ceiling_color != -1)
		free_and_print_error(game, "Error: Duplicate ceiling color\n");
	map_line++;
	map_line = ignore_spaces(map_line);
	get_color(game, map_line, 'C');
}

void	get_f_color(t_game *game, char *map_line)
{
	if (game->map->floor_color != -1)
		free_and_print_error(game, "Error: Duplicate floor color\n");
	map_line++;
	map_line = ignore_spaces(map_line);
	get_color(game, map_line, 'F');
}
