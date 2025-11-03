/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:11:16 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/09 19:02:26 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	print_map(t_map *map)
{
	size_t	i;

	if (map)
	{
		printf(CYAN "Resolution:" NC " %d x %d\n", map->screen_width, \
map->screen_height);
		printf(CYAN "North texture:" NC " %s\n", map->north_texture);
		printf(CYAN "South texture:" NC " %s\n", map->south_texture);
		printf(CYAN "West texture:" NC " %s\n", map->west_texture);
		printf(CYAN "East texture:" NC " %s\n", map->east_texture);
		printf(CYAN "Floor color:" NC " %s\n", map->floor_color);
		printf(CYAN "Ceiling color:" NC " %s\n", map->ceiling_color);
		printf(CYAN "Map lines:\n" NC);
		if (map->map_lines)
		{
			i = 0;
			while (map->map_lines[i])
			{
				printf("[%s]\n", map->map_lines[i]);
				i++;
			}
		}
	}
	else
		printf(CYAN "NULL" NC);
}

void	print_floodfill_map(t_map *map)
{
	size_t	i;

	if (map)
	{
		if (map->flood_fill_map)
		{
			printf(CYAN "Map after applying flood fill algorithm:\n" NC);
			i = 0;
			while (map->flood_fill_map[i])
			{
				printf("[%s]\n", map->flood_fill_map[i]);
				i++;
			}
		}
	}
	else
		printf(CYAN "NULL" NC);
}
