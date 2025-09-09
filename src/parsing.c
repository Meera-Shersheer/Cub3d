/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:17:15 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/09 21:32:06 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	classify_resolution(char *line, t_map *map)
{
	if (line[0] == 'R' && line[1] == ' ')
	{
		if (map->screen_width >= 0 || map->screen_height >= 0)
			error_exit(map, "Resolution defined more than once");
		map->screen_width = ft_atoi(line + 2);
		map->screen_height = ft_atoi(ft_strchr(line + 2, ' '));
	}
}

void	classify_directional_textures(char *line, t_map *map)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (map->north_texture)
			error_exit(map, "North texture defined more than once");
		map->north_texture = ft_strdup( line + 3);
		if(!map->north_texture)
			error_exit(map, "malloc");
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if (map->south_texture)
			error_exit(map, "South texture defined more than once");
		map->south_texture = ft_strdup( line + 3);
		if(!map->south_texture)
			error_exit(map, "malloc");
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if (map->west_texture)
			error_exit(map, "West texture defined more than once");
		map->west_texture = ft_strdup( line + 3);
		if(!map->west_texture)
			error_exit(map, "malloc");
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (map->east_texture)
			error_exit(map, "East texture defined more than once");
		map->east_texture = ft_strdup( line + 3);
		if(!map->east_texture )
			error_exit(map, "malloc");
	}
}

void	classify_colors_and_sprite(char *line, t_map *map)
{
	if (line[0] == 'F')
	{
		if (map->floor_color)
			error_exit(map, "Floor color defined more than once");
		map->floor_color = ft_strdup(line + 2);
		if (!map->floor_color)
			error_exit(map, "malloc");
	}
	else if (line[0] == 'C')
	{
		if (map->ceiling_color)
			error_exit(map, "Ceiling color defined more than once");
		map->ceiling_color = ft_strdup(line + 2);
		if (!map->ceiling_color)
			error_exit(map, "malloc");
	}
}

void	classify_map_lines(char **lines, t_map *map)
{
	size_t	i;
	size_t	map_index;

	i = 0;
	map_index = 0;
	while (lines[i])
	{
		if (lines[i][0] == '0' || lines[i][0] == '1' || lines[i][0] == '2')
		{
			map->map_lines[map_index] = ft_strdup(lines[i]);
			if (!(map->map_lines[map_index]))
				error_exit(map, "malloc");
			map_index++;
		}
		i++;
	}
	map->map_lines[map_index] = NULL;
}

void	classify_lines(char **lines, t_map *map)
{
	 size_t	i;

	i = 0;
	if(!lines || !map)
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
			classify_colors_and_sprite(lines[i], map);
		else if (!(lines[i][0] >= '0' && lines[i][0] <= '2'))
		{
			error_exit(map, "Unknown or extra line detected");
		}
		i++;
	}
	classify_map_lines(lines, map);
	validate_map_values(map);
	print_map(map);
}
