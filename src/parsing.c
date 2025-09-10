/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:32:51 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/10 06:09:08 by aalmahas         ###   ########.fr       */
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
			classify_colors_and_sprite(lines[i], map);
		else if (!(lines[i][0] >= '0' && lines[i][0] <= '2'))
		{
			error_exit(map, "Unknown or extra line detected");
		}
		i++;
	}
	classify_map_lines(lines, map);
	validate_map_values(map);
}
