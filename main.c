/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:06:35 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 12:48:57 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	
	if (!validation(argc, argv))
		print_error("Error: Validation failed\n");
	return (0);
}
