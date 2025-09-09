/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:28:15 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/09 17:36:26 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_map(t_map *map, size_t line_count)
{
	size_t	i;

	map->north_texture = NULL;
	map->south_texture = NULL;
	map->west_texture = NULL;
	map->east_texture = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	map->map_lines = malloc(sizeof(char *) * (line_count + 1));
	if (!map->map_lines)
	{
		perror("Erorr\nmalloc");
		exit(1);
	}
	i = 0;
	while (i < line_count + 1)
	{
		map->map_lines[i] = NULL;
		i++;
	}
}

void	validate_map_values(t_map *map)
{
	if (map->screen_width <= 0 || map->screen_height <= 0)
		error_exit("Resolution missing or invalid");
	if (!map->north_texture)
		error_exit("North texture missing");
	if (!map->south_texture)
		error_exit("South texture missing");
	if (!map->west_texture)
		error_exit("West texture missing");
	if (!map->east_texture)
		error_exit("East texture missing");
	if (!map->floor_color)
		error_exit("Floor color missing");
	if (!map->ceiling_color)
		error_exit("Ceiling color missing");
	if (!map->map_lines || !map->map_lines[0])
		error_exit("Map lines missing");
}


void	print_map(t_map *map)
{
	size_t	i;

	printf("Resolution: %d x %d\n", map->screen_width, map->screen_height);
	printf("North texture: %s\n", map->north_texture);
	printf("South texture: %s\n", map->south_texture);
	printf("West texture: %s\n", map->west_texture);
	printf("East texture: %s\n", map->east_texture);
	printf("Floor color: %s\n", map->floor_color);
	printf("Ceiling color: %s\n", map->ceiling_color);
	printf("Map lines:\n");
	if (map->map_lines)
	{
		i = 0;
		while (map->map_lines[i])
		{
			printf("%s\n", map->map_lines[i]);
			i++;
		}
	}
}
