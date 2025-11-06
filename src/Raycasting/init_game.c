/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:43:53 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/06 21:49:34 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_game(int argc, char *argv[], t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		error_exit(NULL, "malloc failure");
	ft_bzero(game->map, sizeof(t_map));
	game->mini_tile = 16;
	game->mouse_last_x = -1;
	game->wall_distances = NULL;
	if (parsing(argc, argv, game))
		error_exit2(game, NULL);
	place_keys_and_door(game);
	game->mlx = mlx_init(W_SCREEN, H_SCREEN, "Cub3d Game", true);
	if (!game->mlx)
		error_exit2(game, "mlx initializing failure");
	game->won = 0;
	init_textures(game);
	init_key_animation_frames(game);
	init_sprites_allocation(game);
	init_sprites_map_scan(game);
	print_start_header();
}
