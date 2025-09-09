/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:11:16 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/09 23:36:02 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	print_map(t_map *map)
{
	size_t	i;

	if (map)
	{
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
	else
		printf("NULL");
}
