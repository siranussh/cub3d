/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:43:52 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/18 12:44:14 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_path(char *path)
{
	char	*str;

	if (!path)
		return (0);
	if (ft_strchr(path, ' '))
		return (0);
	str = ft_strrchr(path, '.');
	if (!str || ft_strlen(str) > 4)
		return (0);
	if (ft_strncmp(str, ".cub", 4) != 0)
		return (0);
	return (1);
}
