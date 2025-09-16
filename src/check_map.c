/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:41:05 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/16 19:43:30 by mshershe         ###   ########.fr       */
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
	if (!check_map_order(lines))
		error_exit(map, "Map must be last element in file");
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
	map->flood_fill_map = cpy_matrix(map->map_lines);
	if (map->flood_fill_map == NULL)
	{
		free_map(map);
		return (1);
	}
	check_playable_area(map);
	return (0);
}

/*int movement;
movement = floodfill(map, map->flood_fill_map, x, y);
	if (movement <= 1)
		error_exit(map, "Player is stuck and cannot move");*/
void	check_playable_area( t_map *map)
{
	int	x;
	int	y;

	if (!map)
		error_exit(map, "No map to check");
	check_player_position(map);
	x = get_player_x_pos(map->map_lines);
	y = get_player_y_pos(map->map_lines);
	if (x < 0 || y < 0)
		error_exit(map, "player position is out of bound");
	floodfill(map, map->flood_fill_map, x, y);
	print_floodfill_map(map);
	printf(GREEN "-----------------------------------------------\n" NC);
}

int	check_map(char **av, t_map *map)
{
	char		*content;

	if (read_map(av, &content))
		return (1);
	if (process_map(content, map))
		return (1);
	validate_textures(map);
	print_map(map);
	return (0);
}
