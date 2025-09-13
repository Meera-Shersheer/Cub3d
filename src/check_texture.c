/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:24:53 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/12 22:24:16 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_file(t_map *map, const char *path, const char *name)
{
	int	fd;

	if (!path || !*path)
		error_exit(map, name);
	if (path[strlen(path) - 1] == '/')
		error_exit(map, "Texture path must include file name");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(map, name);
	close(fd);
}

void	validate_textures(t_map *map)
{
	check_file(map, map->north_texture, "North texture file not found");
	check_file(map, map->south_texture, "South texture file not found");
	check_file(map, map->west_texture, "West texture file not found");
	check_file(map, map->east_texture, "East texture file not found");
}
