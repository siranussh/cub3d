/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 14:06:35 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/21 16:20:14 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	int	fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	line = get_map_lines(fd);
	printf("line=%s\n", line);
	return (0);
}
