/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 11:50:41 by anavagya          #+#    #+#             */
/*   Updated: 2026/02/02 16:28:01 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void	free_and_print_error(t_game *game, char *str)
{
	if (game)
		free_game(game);
	ft_putstr_fd(str, 2);
	exit(1);
}
