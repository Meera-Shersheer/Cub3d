/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_key_reach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:41:48 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/08 17:21:56 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	reach_keys(t_map *map, char **grid, int x, int y)
{
	int	count;

	if (x < 0 || y < 0 || y >= (int)ft_strlen_d(grid))
		return (0);
	if (x >= (int)ft_strlen(grid[y]))
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'D' || grid[y][x] == 'V')
		return (0);
	count = 0;
	if (grid[y][x] == 'K')
		count = 1;
	grid[y][x] = 'V';
	count += reach_keys(map, grid, x - 1, y);
	count += reach_keys(map, grid, x + 1, y);
	count += reach_keys(map, grid, x, y - 1);
	count += reach_keys(map, grid, x, y + 1);
	return (count);
}

int	reach_door(t_map *map, char **grid, int x, int y)
{
	int	count;

	if (x < 0 || y < 0 || y >= (int)ft_strlen_d(grid))
		return (0);
	if (x >= (int)ft_strlen(grid[y]))
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'K' || grid[y][x] == 'V')
		return (0);
	count = 0;
	if (grid[y][x] == 'D')
		count = 1;
	grid[y][x] = 'V';
	count += reach_door(map, grid, x - 1, y);
	count += reach_door(map, grid, x + 1, y);
	count += reach_door(map, grid, x, y - 1);
	count += reach_door(map, grid, x, y + 1);
	return (count > 0);
}

int	door_reachable(t_game *g, char **map)
{
	char	**grid_copy;
	int		px;
	int		py;
	int		reached;

	(void)map;
	grid_copy = cpy_matrix(map);
	if (!grid_copy)
		return (0);
	px = get_player_x_pos(grid_copy);
	py = get_player_y_pos(grid_copy);
	reached = reach_door(g->map, grid_copy, px, py);
	ft_free(grid_copy);
	return (reached == 1);
}

int	keys_reachable(t_game *g, char **map)
{
	char	**grid_copy;
	int		px;
	int		py;
	int		reached;

(void)map;
	grid_copy = cpy_matrix(map);
	if (!grid_copy)
		return (0);
	px = get_player_x_pos(grid_copy);
	py = get_player_y_pos(grid_copy);
	reached = reach_keys(g->map, grid_copy, px, py);
	ft_free(grid_copy);
	return (reached == g->total_keys);
}
