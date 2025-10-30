/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:36:46 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/30 20:58:29 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int pseudo_random(int max)
{
	struct timeval tv;
	
	if (max <= 0)
		return (0);
	gettimeofday(&tv, NULL);
	return ((tv.tv_usec ^ tv.tv_sec) % max);
}

void check_key_pickup(t_game *g)
{
    int px ;
    int py ;
	
	if (!g || !g->player || !g->map || !g->map->map_lines)
		return;
	if (g->map->screen_height <= 0 || g->map->screen_width <= 0)
		return;
	px = (int)(g->player->x / g->mini_tile);
	py = (int)(g->player->y / g->mini_tile);
	
	if (py < 0 || py >= g->map->screen_height)
		return;
	if (px < 0 || px >= g->map->screen_width)
		return;
	if (!g->map->map_lines[py])
		return;
    if (g->map->map_lines[py][px] == 'K')
    {
        g->collected_keys++;
        g->map->map_lines[py][px] = '0';
		check_key_sprite_pickup(g, px, py);
        printf("🔑 You picked up a key! (%d/%d)\n", g->collected_keys, g->total_keys);
        if (g->map_2d)
			color_square_map2d(g, 0xFFF3C5B9, g->map_2d, px * g->mini_tile, py * g->mini_tile);
		if (g->collected_keys == g->total_keys)
			g->door_open = 1;
	}
}

void check_key_sprite_pickup(t_game *g, int tile_x, int tile_y)
{
	int i;

	if (!g || !g->sprites || !g->sprites->sprites ||  g->sprites->count <= 0)
		return;
	i = 0;
	while (i < g->sprites->count)
	{
		if (!g->sprites->sprites[i])
		{
			i++;
			continue;
		}
		if (g->sprites->sprites[i]->map_tile_x == tile_x && g->sprites->sprites[i]->map_tile_y == tile_y)
			g->sprites->sprites[i]->collected = 1;
		i++;	
	}
}

void check_door(t_game *g)
{
	int px;
	int py;
	
	if (!g || !g->player || !g->map || !g->map->map_lines)
		return;
	if (g->map->screen_height <= 0 || g->map->screen_width <= 0)
		return;
	px = (int)(g->player->x / g->mini_tile);
	py = (int)(g->player->y / g->mini_tile);

	if (py < 0 || py >= g->map->screen_height)
		return;
	if (px < 0 || px >= g->map->screen_width)
		return;
	if (!g->map->map_lines[py])
		return;
	
	if (g->map->map_lines[py][px] == 'D')
	{
		if (g->collected_keys == g->total_keys)
		{
			printf("🚪 Door opened! You win! 🎉\n");
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