/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:34:58 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/20 13:09:37 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_isspace(int a)
{
	if (a == 32 || (a >= 9 && a <= 13))
		return (1);
	return (0);
}

int	str_is_only_spaces(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (ft_isspace(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

char	*ignore_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (ft_isspace(*str) == 1)
			str++;
		else
			break ;
	}
	return (str);
}

static int	is_map_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		return (0);
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'E' && s[i] != 'W' && s[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	find_map_start(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (is_map_line(&line[i]))
			return (i);
		while (line[i] && line[i] != '\n')
			i++;
		if (line[i] == '\n')
			i++;
	}
	return (-1);
}
