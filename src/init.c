/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:28:15 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/08 16:36:16 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_textures_and_colors(t_map *map)
{
	map->north_texture = NULL;
	map->south_texture = NULL;
	map->west_texture = NULL;
	map->east_texture = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	map->screen_height = -1;
	map->screen_width = -1;
	map->f_color.r = -1;
	map->f_color.g = -1;
	map->f_color.b = -1;
	map->c_color.r = -1;
	map->c_color.g = -1;
	map->c_color.b = -1;
	map->msg = NULL;
	map->flood_fill_map = NULL;
}

static void	init_map_lines(t_map *map, size_t line_count)
{
	size_t	i;

	map->map_lines = malloc(sizeof(char *) * (line_count + 1));
	if (!map->map_lines)
		error_exit(map, "Malloc Failure");
	i = 0;
	while (i < line_count + 1)
	{
		map->map_lines[i] = NULL;
		i++;
	}
}

void	init_map(t_map *map, size_t line_count)
{
	init_textures_and_colors(map);
	init_map_lines(map, line_count);
}

void	validate_map_values(t_map *map)
{
	if (!map->north_texture && !map->south_texture && !map->west_texture
		&& !map->east_texture)
		error_exit(map, "No textures available");
	if (!map->north_texture)
		error_exit(map, "North texture missing");
	if (!map->south_texture)
		error_exit(map, "South texture missing");
	if (!map->west_texture)
		error_exit(map, "West texture missing");
	if (!map->east_texture)
		error_exit(map, "East texture missing");
	if (!map->floor_color)
	{
		if (!map->ceiling_color)
			error_exit(map, "No color specifications");
		else
			error_exit(map, "Floor color missing");
	}
	if (!map->ceiling_color)
		error_exit(map, "Ceiling color missing");
	if (!map->map_lines || !map->map_lines[0])
		error_exit(map, "Map lines missing");
	check_color(map);
	check_map_values(map);
}

void	check_color(t_map *map)
{
	int	n;

	n = parse_color_line(map->ceiling_color, &map->c_color);
	if (n != 0)
	{
		if (parse_color_line(map->floor_color, &map->f_color) != 0)
			error_exit(map, "Invalid colors specification in the map");
		else
			error_exit(map, "Invalid ceiling color value");
	}
	n = parse_color_line(map->floor_color, &map->f_color);
	if (n != 0)
		error_exit(map, "Invalid floor color value");
}
