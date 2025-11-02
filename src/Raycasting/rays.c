/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:10:16 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/02 20:52:01 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	init_scene_images_and_distances(t_game *game)
{
	int	i;

	if (!game)
		exit(1);
	game->rays = mlx_new_image(game->mlx, game->mini_tile
			* (game->map->screen_width), game->mini_tile
			* (game->map->screen_height));
	game->scene_3d = mlx_new_image(game->mlx, W_TILE
			* (game->map->screen_width), W_TILE * (game->map->screen_height));
	if (!game->rays || !game->scene_3d)
		error_exit(NULL, "image initialization failure");
	game->wall_distances = malloc(sizeof(float) * game->scene_3d->width);
	if (!game->wall_distances)
		error_exit(game->map, "malloc failure for wall_distances");
	i = 0;
	while (i < (int)game->scene_3d->width)
	{
		game->wall_distances[i] = 10000.0f;
		i++;
	}
	i = 0;
	while (i < game->mini_tile * game->map->screen_width)
	{
		camera_x = 2 * i / (float)game->rays->width - 1;
    	an = game->player->angle + atanf(camera_x * tanf(FOV/ 2));
		cast_rays(game, an);
		i++;
	}
}

void	draw_scene_and_rays(t_game *game)
{
	if (!game)
		exit(1);
	init_scene_images_and_distances(game);
	dda(game);
	if (mlx_image_to_window(game->mlx, game->rays, 0, 0) < 0)
		error_exit(NULL, "image display failure");
	if (mlx_image_to_window(game->mlx, game->scene_3d, 0, 0) < 0)
		error_exit(NULL, "image display failure");
	mlx_set_instance_depth(&game->scene_3d->instances[0], -1);
}

void	dda(t_game *game)
{
	float	camera_x;
	float	an;
	int		i;

	if (!game || !game->scene_3d || !game->player || !game->rays)
		error_exit(NULL, "cast ray failure");
	ft_memset((uint32_t *)game->rays->pixels, 0, game->rays->width
		* game->rays->height * sizeof(uint32_t));
	i = 0;
	while (i < (int)game->scene_3d->width)
	{
		camera_x = 2 * i / (float)game->scene_3d->width - 1;
		an = game->player->angle + atanf(camera_x * tanf(FOV / 2));
		draw_single_col(game, an, i);
		i++;
	}
	i = 0;
	while (i < game->mini_tile * game->map->screen_width)
	{
		camera_x = 2 * i / (float)game->rays->width - 1;
		an = game->player->angle + atanf(camera_x * tanf(FOV / 2));
		cast_rays(game, an);
		i++;
	}
}
