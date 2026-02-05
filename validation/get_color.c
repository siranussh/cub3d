/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:58:09 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/05 15:36:27 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_rgb(t_game *game, char *map_line)
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
	r = ft_atoi(color_rgb[0]);
	g = ft_atoi(color_rgb[1]);
	b = ft_atoi(color_rgb[2]);
	ft_free(color_rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		free_and_print_error(game, "Error: Invalid rgb values\n");
	return (r * 65536 + g * 256 + b);
}

void	get_color(t_game *game, char *line, char type)
{
	int	color;

	color = parse_rgb(game, line);
	if (type == 'F')
		game->map->floor_color = color;
	else if (type == 'C')
		game->map->ceiling_color = color;
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
