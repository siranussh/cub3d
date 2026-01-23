/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:34:58 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/23 13:31:45 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3d.h"

int	ft_isspace(int a)
{
	if (a == 32 || (a >= 9 && a <= 13))
		return (1);
	return (0);
}

char	*ignore_spaces(char *str)
{
	if (!str)
		return (NULL);
	while(*str)
	{
		if (ft_isspace(*str) == 1)
			str++;
		else
			break;
	}
	return (str);
}
