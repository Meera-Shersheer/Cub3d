/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:43:53 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/05 15:53:36 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_game(int argc, char *argv[], t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		error_exit(NULL, "malloc failure");
	ft_bzero(game->map , sizeof(t_map));
	game->w_tile = W_TILE;
	game->mini_tile = MINI_TILE;
	game->mouse_last_x = -1;
	game->wall_distances = NULL;
	if (parsing(argc, argv, game))
		error_exit(game->map, "parsing failure");
	place_keys_and_door(game);
	game->mlx = mlx_init(700, 700, "Cub3d Game", true);///edit 
	if (!game->mlx)
		error_exit(game->map, "mlx initializing failure");
	game->won = 0;
	init_textures(game);
	init_key_animation_frames(game);
	init_sprites_allocation(game);
	init_sprites_map_scan(game);
}
