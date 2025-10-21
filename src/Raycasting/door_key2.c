/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:36:46 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/21 23:38:50 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int pseudo_random(int max)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_usec ^ tv.tv_sec) % max);
}




void check_key_pickup(t_game *g)
{
    int px = (int)(g->player->x / MINI_TILE);
    int py = (int)(g->player->y / MINI_TILE);

    if (g->map->map_lines[py][px] == 'K')
    {
        g->collected_keys++;
        g->map->map_lines[py][px] = '0';
        printf("🔑 You picked up a key! (%d/%d)\n", g->collected_keys, g->total_keys);
        color_square_map2d(0xFFF3C5B9, g->map_2d, px * MINI_TILE, py * MINI_TILE);
    }
}



void check_door(t_game *g)
{
	int px = (int)(g->player->x / MINI_TILE);
	int py = (int)(g->player->y / MINI_TILE);

	if (g->map->map_lines[py][px] == 'D')
	{
		if (g->collected_keys == g->total_keys)
		{
			printf("🚪 Door opened! You win! 🎉\n");
			g->door_open = 1;
			mlx_close_window(g->mlx);
		}
		else
		{
			printf("🚫 Door is locked! Collect all keys first (%d/%d)\n",
				g->collected_keys, g->total_keys);
		}
	}
}
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
	count += reach_keys(map, grid, x - 1, y - 1);
	count += reach_keys(map, grid, x - 1, y + 1);
	count += reach_keys(map, grid, x + 1, y - 1);
	count += reach_keys(map, grid, x + 1, y + 1);
	return (count);
}