/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 20:18:25 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/08 17:22:27 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	place_keys(char **map, int screen_width, int screen_height, int total_keys)
{
	int	placed;
	int	attempts;
	int	x;
	int	y;
	int	max_attempts;

	placed = 0;
	attempts = 0;
	max_attempts = 1000;
	while (placed < total_keys && attempts < max_attempts)
	{
		y = pseudo_random(screen_height);
		x = pseudo_random(screen_width);
		if (map[y][x] == '0')
		{
			map[y][x] = 'K';
			placed++;
		}
		attempts++;
	}
	return (placed == total_keys);
}

int	place_door(char **map, t_game *g)
{
	int	attempts;
	int	x;
	int	y;
	int	max_attempts;

	attempts = 0;
	max_attempts = 1000;
	while (attempts < max_attempts)
	{
		y = pseudo_random(g->map->screen_height);
		x = pseudo_random(g->map->screen_width);
		if (map[y][x] == '1' && ((x > 0 && map[y][x - 1] == '0')
				|| (x < g->map->screen_width - 1 && map[y][x + 1] == '0')
				|| (y > 0 && map[y - 1][x] == '0') || (y < g->map->screen_height
					- 1 && map[y + 1][x] == '0')))
		{
			map[y][x] = 'D';
			g->door_x = x;
			g->door_y = y;
			return (1);
		}
		attempts++;
	}
	return (0);
}

static int	try_place(t_game *g, char **temp_map)
{
	g->total_keys = pseudo_random(3) + 2;
	g->collected_keys = 0;
	g->door_open = 0;
	if (!place_keys(temp_map, g->map->screen_width, g->map->screen_height,
			g->total_keys))
		return (0);
	if (!place_door(temp_map, g))
		return (0);
	if (!keys_reachable(g, temp_map))
		return (0);
	if (!door_reachable(g, temp_map))
		return (0);
	return (1);
}

void	place_keys_and_door(t_game *g)
{
	int		retries;
	int		max_retries;
	char	**temp_map;

	retries = 0;
	max_retries = 30;
	while (retries < max_retries)
	{
		temp_map = cpy_matrix(g->map->map_lines);
		if (!temp_map)
			error_exit(g->map, "Malloc Failure");
		if (try_place(g, temp_map))
		{
			ft_free(g->map->map_lines);
			g->map->map_lines = temp_map;
			return ;
		}
		ft_free(temp_map);
		retries++;
	}
	error_exit(g->map,
		"❌ Failed to place keys and door after multiple attempts");
}
