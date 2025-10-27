/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:36:46 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/27 19:17:50 by mshershe         ###   ########.fr       */
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
		check_key_sprite_pickup(g, px, py);
        printf("🔑 You picked up a key! (%d/%d)\n", g->collected_keys, g->total_keys);
        color_square_map2d(0xFFF3C5B9, g->map_2d, px * MINI_TILE, py * MINI_TILE);
		if (g->collected_keys == g->total_keys)
			g->door_open = 1;
	}
}
void check_key_sprite_pickup(t_game *g, int tile_x, int tile_y)
{
	int i;

	i = 0;
	while (i < g->sprites->count)
	{
		if (g->sprites->sprites[i]->map_tile_x == tile_x && g->sprites->sprites[i]->map_tile_y == tile_y)
		{
			g->sprites->sprites[i]->collected = 1;
			break;
		}
		i++;	
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
			puts("🚪 Door opened! You win! 🎉");
			g->won = 1;
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