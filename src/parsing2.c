/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:17:15 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/09 23:32:32 by aalmahas         ###   ########.fr       */
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

void	set_texture(char **texture_field, const char *line, t_map *map,
		const char *err_msg)
{
	if (*texture_field)
		error_exit(map, err_msg);
	*texture_field = ft_strdup(line);
	if (!*texture_field)
		error_exit(map, "malloc failed");
}

void	classify_directional_textures(char *line, t_map *map)
{
	if (line[0] == 'N' && line[1] == 'O')
		set_texture(&map->north_texture, line + 3, map,
			"North texture defined more than once");
	else if (line[0] == 'S' && line[1] == 'O')
		set_texture(&map->south_texture, line + 3, map,
			"South texture defined more than once");
	else if (line[0] == 'W' && line[1] == 'E')
		set_texture(&map->west_texture, line + 3, map,
			"West texture defined more than once");
	else if (line[0] == 'E' && line[1] == 'A')
		set_texture(&map->east_texture, line + 3, map,
			"East texture defined more than once");
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
