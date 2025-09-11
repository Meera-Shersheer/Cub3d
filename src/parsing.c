/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:32:51 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/11 10:44:58 by aalmahas         ###   ########.fr       */
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

	i = 0;
	map_index = 0;
	map_started = 0;
	while (lines[i])
	{
		if (lines[i][0] == '0' || lines[i][0] == '1')
		{
			if (!map_started)
				map_started = 1;
			add_map_line(map, lines[i], &map_index);
		}
		else if (map_started)
			error_exit(map, "Map must be the last element in the file");
		i++;
	}
	map->map_lines[map_index] = NULL;
}

void	classify_lines(char **lines, t_map *map)
{
	size_t	i;

	i = 0;
	if (!lines || !map)
		error_exit(map, "NULL Variable");
	while (lines[i])
	{
		if (lines[i][0] == 'R')
			classify_resolution(lines[i], map);
		else if (lines[i][0] == 'N' || lines[i][0] == 'S' || lines[i][0] == 'W'
			|| lines[i][0] == 'E')
			classify_directional_textures(lines[i], map);
		else if (lines[i][0] == 'F' || lines[i][0] == 'C' || (lines[i][0] == 'S'
				&& lines[i][1] == ' '))
			classify_colors(lines[i], map);
		else if (!(lines[i][0] >= '0' && lines[i][0] <= '2'))
		{
			error_exit(map, "Unknown or extra line detected");
		}
		i++;
	}
	classify_map_lines(lines, map);
	validate_map_values(map);
}
