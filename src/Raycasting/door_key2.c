/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 23:36:46 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/02 20:49:40 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	is_valid_player_tile(t_game *g, int px, int py)
{
	if (!g || !g->player || !g->map || !g->map->map_lines)
		return (0);
	if (g->map->screen_height <= 0 || g->map->screen_width <= 0)
		return (0);
	if (py < 0 || py >= g->map->screen_height)
		return (0);
	if (px < 0 || px >= g->map->screen_width)
		return (0);
	if (!g->map->map_lines[py])
		return (0);
	return (1);
}

void	check_key_pickup(t_game *g)
{
	int	px;
	int	py;

	if (!g || !g->player)
		return ;
	px = (int)(g->player->x / g->mini_tile);
	py = (int)(g->player->y / g->mini_tile);
	if (!is_valid_player_tile(g, px, py))
		return ;
	if (g->map->map_lines[py][px] == 'K')
	{
		g->collected_keys++;
		g->map->map_lines[py][px] = '0';
		check_key_sprite_pickup(g, px, py);
		printf("🔑 You picked up a key! (%d/%d)\n", g->collected_keys,
			g->total_keys);
		if (g->map_2d)
			color_square_map2d(g, 0xFFF3C5B9, px * g->mini_tile, py
				* g->mini_tile);
		if (g->collected_keys == g->total_keys)
			g->door_open = 1;
	}
}

void	check_key_sprite_pickup(t_game *g, int tile_x, int tile_y)
{
	int	i;

	if (!g || !g->sprites || !g->sprites->sprites || g->sprites->count <= 0)
		return ;
	i = 0;
	while (i < g->sprites->count)
	{
		if (!g->sprites->sprites[i])
		{
			i++;
			continue ;
		}
		if (g->sprites->sprites[i]->map_tile_x == tile_x
			&& g->sprites->sprites[i]->map_tile_y == tile_y)
			g->sprites->sprites[i]->collected = 1;
		i++;
	}
}

void	check_door(t_game *g)
{
	int	px;
	int	py;

	if (!g || !g->player || !g->map || !g->map->map_lines)
		return ;
	if (g->map->screen_height <= 0 || g->map->screen_width <= 0)
		return ;
	px = (int)(g->player->x / g->mini_tile);
	py = (int)(g->player->y / g->mini_tile);
	if (py < 0 || py >= g->map->screen_height)
		return ;
	if (px < 0 || px >= g->map->screen_width)
		return ;
	if (!g->map->map_lines[py])
		return ;
	if (g->map->map_lines[py][px] == 'D')
	{
		if (g->collected_keys == g->total_keys)
		{
			printf("🚪 Door opened! You win! 🎉\n");
			g->won = 1;
		}
	}
}
