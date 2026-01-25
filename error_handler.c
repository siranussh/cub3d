/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:50:41 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/25 14:21:12 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "includes/cub3d.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	free_map_print_error(t_map *map, char *str)
{
	if (map)
		free_map(map);
	ft_putstr_fd(str, 2);
	exit(1);
}
