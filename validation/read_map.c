/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:36:58 by anavagya          #+#    #+#             */
/*   Updated: 2026/01/21 18:22:51 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_map_lines(int fd)
{
	char	*tmp;
	char	*line;

	tmp = NULL;
	line = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)//|| tmp[0] == '\n')
		{
			get_next_line(-1);
			if (!tmp)
				break ;
			free(tmp);
			free(line);
			return ("\n");
		}
		if (!line)
			line = ft_gnl_strdup(tmp);
		else
			line = ft_gnl_strjoin(line, tmp);
		free(tmp);
	}
	return (line);
}

void	parse_map(t_map *m, int fd, char *line)
{
	char	**map;
	char	**textures;
	int		texture_len;
	int		i;

	if (!line || !*line)
	{
		close(fd);
		free(line);
		// free(game);
		print_error("Error: Map file is empty.\n");
	}
	if (*line == '\n')
	{
		close(fd);
		// free(game);
		print_error("Error: Invalid map format.\n");
	}
	map = ft_split(line, '\n');
	i = 0;
	while(i < 4)
	{
		while(*map[i])
		{
			if (ft_isspace(*map[i]) == 1)
				i++;
			if (ft_strcmp(map[i], "NO"))
			{
				m->no_tx = get_texture_path(map[i]);
				if (!m->no_tx)
					return ;
			}
			else if(ft_strcmp(map[i], "EA"))
			{
				m->ea_tx = get_texture_path(map[i]);
				if (!m->ea_tx)
					return ;
			}
			else if (ft_strcmp(map[i], "WE"))
			{
				m->we_tx = get_texture_path(map[i]);
				if (!m->we_tx)
					return ;
			}
			else if(ft_strcmp(map[i], "SO"))
			{
				m->so_tx = get_texture_path(map[i]);
				if (!m->so_tx)
					return ;
			}
			map[i]++;
		}
		i++;
	}
	if (!map)
	{
		close(fd);
		free(line);
		free_map(map);
		// free(game);
		print_error("Error: Invalid map format or malloc error.\n");
	}
}

// void	validate_map(t_game *game, int fd, char *line)
// {
// 	if (!valid_map(game, game->map))
// 	{
// 		close(fd);
// 		free(line);
// 		free_map(game->map);
// 		free(game);
// 		exit(1);
// 	}
// 	if (!check_reachability(game))
// 	{
// 		close(fd);
// 		free(line);
// 		free_map(game->map);
// 		free(game);
// 		print_error("Error: Map has unreachable collectibles or exit.\n");
// 	}
// 	if (!map_size(game))
// 	{
// 		close(fd);
// 		free(line);
// 		free_map(game->map);
// 		free(game);
// 		print_error("Error: Map is too big.\n");
// 	}
// }

char	**load_map(char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		// free(game);
		print_error("Error: Can't open file.\n");
	}
	line = get_map_lines(fd);
	parse_map(fd, line);
	// width = ft_strlen(game->map[0]);
	// while (game->map[game->height])
	// 	game->height++;
	// validate_map(game, fd, line);
	close(fd);
	free(line);
	return (game->map);
}
