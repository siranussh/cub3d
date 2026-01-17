/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:54:22 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/17 17:34:38 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validation(int argc, char **argv)
{
	if (argc > 2)
	{
		ft_putendl_fd("Error: Too many arguments", 2);
		return (0);
	}
	return (1);
}
