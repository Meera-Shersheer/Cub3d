/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:32:51 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/13 23:10:33 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	skip_spaces(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}

void	classify_resolution(char *line, t_map *map)
{
	int	i;

	if (line[0] == 'R')
	{
		if (map->screen_width >= 0 || map->screen_height >= 0)
			error_exit(map, "Resolution defined more than once");
		i = 1;
		i = skip_spaces(line, i);
		map->screen_width = ft_atoi(line + i);
		while (line[i] && line[i] != ' ')
			i++;
		i = skip_spaces(line, i);
		map->screen_height = ft_atoi(line + i);
	}
}

void	add_map_line(t_map *map, char *line, size_t *map_index)
{
	map->map_lines[*map_index] = ft_strdup(line);
	if (!map->map_lines[*map_index])
		error_exit(map, "malloc");
	(*map_index)++;
}

void	classify_map_lines(char **lines, t_map *map)
{
	size_t	i;
	size_t	map_index;
	int		map_started;
	int		j;

	i = 0;
	map_index = 0;
	map_started = 0;
	while (lines[i])
	{
		j = skip_spaces(lines[i], 0);
		if (map_started && lines[i][j] == '\0')
			error_exit(map, "Empty line inside map");
		if (lines[i][j] == '0' || lines[i][j] == '1')
		{
			if (!map_started)
				map_started = 1;
			add_map_line(map, lines[i] + j, &map_index);
		}
		else if (map_started && lines[i][j] != '\0')
			error_exit(map, "Map must be the last element in the file");
		i++;
	}
	map->map_lines[map_index] = NULL;
}

void	classify_config_lines(char **lines, t_map *map)
{
	size_t	i;
	int		j;
	char	*line_trimmed;

	i = 0;
	while (lines[i])
	{
		line_trimmed = trim_newline(lines[i]);
		j = skip_spaces(line_trimmed, 0);
		if (line_trimmed[j] == 'R')
			classify_resolution(line_trimmed + j, map);
		else if (line_trimmed[j] == 'N' || line_trimmed[j] == 'S'
			|| line_trimmed[j] == 'W' || line_trimmed[j] == 'E')
			classify_directional_textures(line_trimmed + j, map);
		else if (line_trimmed[j] == 'F' || line_trimmed[j] == 'C'
			|| (line_trimmed[j] == 'S' && line_trimmed[j + 1] == ' '))
			classify_colors(line_trimmed + j, map);
		else if (!(line_trimmed[j] >= '0' && line_trimmed[j] <= '2')
			&& line_trimmed[j] != '\0')
			error_exit(map, "Unknown or extra line detected");
		i++;
	}
}
