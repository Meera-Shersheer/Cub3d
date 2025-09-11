/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:17:15 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/11 10:44:21 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_texture(char **texture_field, const char *line, t_map *map,
		const char *err_msg)
{
	if (*texture_field)
		error_exit(map, err_msg);
	*texture_field = ft_strdup(line);
	if (!*texture_field)
		error_exit(map, "malloc failed");
}

void	handle_ns_textures(char *line, t_map *map)
{
	int	i;

	if (line[0] == 'N' && line[1] == 'O')
	{
		i = skip_spaces(line, 2);
		set_texture(&map->north_texture, line + i, map,
			"North texture defined more than once");
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		i = skip_spaces(line, 2);
		set_texture(&map->south_texture, line + i, map,
			"South texture defined more than once");
	}
}

void	handle_we_textures(char *line, t_map *map)
{
	int	i;

	if (line[0] == 'W' && line[1] == 'E')
	{
		i = skip_spaces(line, 2);
		set_texture(&map->west_texture, line + i, map,
			"West texture defined more than once");
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		i = skip_spaces(line, 2);
		set_texture(&map->east_texture, line + i, map,
			"East texture defined more than once");
	}
}

void	classify_directional_textures(char *line, t_map *map)
{
	handle_ns_textures(line, map);
	handle_we_textures(line, map);
}

void	classify_colors(char *line, t_map *map)
{
	int	i;

	if (line[0] == 'F')
	{
		if (map->floor_color)
			error_exit(map, "Floor color defined more than once");
		i = skip_spaces(line, 1);
		map->floor_color = ft_strdup(line + i);
		if (!map->floor_color)
			error_exit(map, "malloc");
	}
	else if (line[0] == 'C')
	{
		if (map->ceiling_color)
			error_exit(map, "Ceiling color defined more than once");
		i = skip_spaces(line, 1);
		map->ceiling_color = ft_strdup(line + i);
		if (!map->ceiling_color)
			error_exit(map, "malloc");
	}
}

