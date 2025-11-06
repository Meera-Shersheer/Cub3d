/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_window_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:51:15 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/06 10:03:20 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// void	adjust_tile_size_to_screen(t_game *game, int map_width, int map_height)
// {
// 	int32_t	max_width;
// 	int32_t	max_height;

// 	max_width = 1920;
// 	max_height = 1080;
// 	while ((map_width * game->w_tile > max_width
// 			|| map_height * game->w_tile > max_height)
// 		&& game->w_tile > MIN_TILE_SIZE)
// 	{
// 		game->w_tile = (int)(game->w_tile * SCALE_FACTOR);
// 		game->mini_tile = game->w_tile / 4;
// 	}
// 	if (map_width * game->w_tile > max_width
// 		|| map_height * game->w_tile > max_height)
// 		error_exit2(game,
// 			"Map too large to fit on screen, even at minimum tile size");
// }
