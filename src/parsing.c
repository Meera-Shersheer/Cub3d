/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:17:15 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/08 21:17:35 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	classify_resolution(char *line, t_map *map)
{
	if (line[0] == 'R' && line[1] == ' ')
	{
		if (map->screen_width != 0 || map->screen_height != 0)
			error_exit("Resolution defined more than once");
		map->screen_width = ft_atoi(line + 2);
		map->screen_height = ft_atoi(ft_strchr(line + 2, ' '));
	}
}

void	classify_directional_textures(char *line, t_map *map)
{
	if (line[0] == 'N' && line[1] == 'O')
	{
		if (map->north_texture)
			error_exit("North texture defined more than once");
		map->north_texture = line + 3;
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		if (map->south_texture)
			error_exit("South texture defined more than once");
		map->south_texture = line + 3;
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		if (map->west_texture)
			error_exit("West texture defined more than once");
		map->west_texture = line + 3;
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		if (map->east_texture)
			error_exit("East texture defined more than once");
		map->east_texture = line + 3;
	}
}

void	classify_colors_and_sprite(char *line, t_map *map)
{
	if (line[0] == 'S' && line[1] == ' ')
	{
		if (map->sprite_texture)
			error_exit("Sprite texture defined more than once");
		map->sprite_texture = line + 2;
	}
	else if (line[0] == 'F')
	{
		if (map->floor_color)
			error_exit("Floor color defined more than once");
		map->floor_color = line + 2;
	}
	else if (line[0] == 'C')
	{
		if (map->ceiling_color)
			error_exit("Ceiling color defined more than once");
		map->ceiling_color = line + 2;
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
			map->map_lines[map_index++] = lines[i];
		i++;
	}
	map->map_lines[map_index] = NULL;
}

void	classify_lines(char **lines, t_map *map)
{
	size_t	i;

	i = 0;
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
			error_exit("Unknown or extra line detected");
		i++;
	}
	classify_map_lines(lines, map);
}
