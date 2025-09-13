/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:41:05 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/13 21:20:53 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	read_map(char **av, char **content)
{
	*content = read_file(av[1]);
	if (!*content)
	{
		printf(RED "Error\nEmpty File\n" NC);
		return (1);
	}
	return (0);
}

void	classify_lines(char **lines, t_map *map)
{
	if (!lines || !map)
		error_exit(map, "NULL Variable");
	classify_config_lines(lines, map);
	classify_map_lines(lines, map);
	validate_map_values(map);
}

int	process_map(char *content, t_map *map)
{
	size_t	total_lines;

	map->cpy_content = split_lines_with_nl(content);
	if (content)
		free(content);
	if (!map->cpy_content)
	{
		printf(RED "Error\nFailed to split lines\n" NC);
		return (1);
	}
	total_lines = 0;
	while ((map->cpy_content)[total_lines])
		total_lines++;
	init_map(map, total_lines);
	classify_lines(map->cpy_content, map);
	return (0);
}

int	check_map(char **av, t_map *map)
{
	char		*content;

	if (read_map(av, &content))
		return (1);
	if (process_map(content, map))
	{
		return (1);
	}
	validate_textures(map);
	print_map(map);
	return (0);
}
