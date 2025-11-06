/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:58:16 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/06 18:49:26 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	color_block(unsigned int color, mlx_image_t *img)
{
	int			i;
	uint32_t	*pixels;

	i = 0;
	if (!img)
		return ;
	pixels = (uint32_t *)img->pixels;
	while (i < (int)(img->width * img->height))
	{
		pixels[i] = color;
		i++;
	}
}

void	draw_player(t_game *game)
{
	if (!game)
		exit(1);
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		error_exit2(game, "malloc failure");
	if (!game->map)
		error_exit2(game, "map failure");
	game->player->img = mlx_new_image(game->mlx, game->mini_tile / 3,
			game->mini_tile / 3);
	if (!game->player->img)
		error_exit2(game, "image initialization failure");
	game->player->x = get_player_x_pos(game->map->map_lines) * game->mini_tile
		+ (game->mini_tile - game->player->img->width) / 2;
	game->player->y = get_player_y_pos(game->map->map_lines) * game->mini_tile
		+ (game->mini_tile - game->player->img->height) / 2;
	game->player->move_speed = game->mini_tile / 3.0f;
	game->player->rot_speed = 0.1f;
	pick_initial_angle(game);
	color_block(0xFFCC00CC, game->player->img);
	if (mlx_image_to_window(game->mlx, game->player->img, game->player->x,
			game->player->y) < 0)
		error_exit2(game, "image display failure");
}

void	pick_initial_angle(t_game *game)
{
	if (!game)
		exit(1);
	if (game->map->initial_look_dir == 'N')
		game->player->angle = -M_PI / 2;
	else if (game->map->initial_look_dir == 'S')
		game->player->angle = M_PI / 2;
	else if (game->map->initial_look_dir == 'W')
		game->player->angle = M_PI;
	else
		game->player->angle = 0;
}

void	draw_map_tile(t_game *game, int x, int y)
{
	int		tile_x;
	int		tile_y;
	char	tile;

	tile_x = x * game->mini_tile;
	tile_y = y * game->mini_tile;
	tile = game->map->map_lines[y][x];
	if (tile == '1')
		color_square_map2d(game, 0xFF230C06, tile_x, tile_y);
	else if (tile == ' ')
		color_square_map2d(game, 0xFF363636, tile_x, tile_y);
	else if (tile == 'K')
	{
		color_square_map2d(game, 0xFFF3C5B9, tile_x, tile_y);
		draw_key_symbol(game, game->map_2d, tile_x, tile_y);
	}
	else if (tile == 'D')
		draw_door_symbol(game, game->map_2d, tile_x, tile_y);
	else
		color_square_map2d(game, 0xFFF3C5B9, tile_x, tile_y);
}
