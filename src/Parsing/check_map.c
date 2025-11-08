/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:41:05 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/08 16:54:03 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	read_map(char **av, char **content, t_game *game)
{
	*content = read_file(av[1], game);
	if (!*content)
	{
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
		error_exit(map, "Malloc Failure");
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
}

int	check_map(char **av, t_game *game)
{
	char		*content;

	if (read_map(av, &content, game))
	{
		printf(RED"Erorr\nEmpty File\n" NC);
		return (1);
	}
	if (process_map(content, game->map))
		return (1);
	validate_textures(game->map);
	game->map->screen_height = ft_strlen_d(game->map->map_lines);
	game->map->screen_width = ft_strlen(game->map->map_lines[0]);
	return (0);
}
