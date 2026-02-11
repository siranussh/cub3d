/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 14:07:21 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/05 15:36:38 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_rgb(char **rgb)
{
	int	i;

	if (double_arr_size(rgb) != 3)
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

int	count_commas(char *line)
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

int	is_only_digits(char *color_rgb)
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
