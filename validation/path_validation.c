/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:56:38 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 14:43:42 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	valid_path(char *path, char *domain)
{
	char	*str;

	if (!path)
		return (0);
	if (ft_strchr(path, ' '))
		return (0);
	if (ft_strcmp(domain, ".xpm") == 0)
		path++;
	str = ft_strchr(path, '.');
	if (!str || ft_strlen(str) > 4)
		return (0);
	if (ft_strncmp(str, domain, ft_strlen(domain)) != 0)
		return (0);
	return (1);
}
