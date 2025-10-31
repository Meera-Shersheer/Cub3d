/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/31 23:26:56 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"


	
	
	/*To test leaks: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=mlx.supp ./cub3D map*/



int	main(int argc, char *argv[])
{
	t_game game;
		
	ft_bzero(&game, sizeof(game));
	game.map = malloc(sizeof(t_map));
	if(!game.map)
		error_exit(NULL, "malloc failure");
	game.w_tile = W_TILE;
	game.mini_tile = MINI_TILE;
	game.mouse_last_x = -1;
	game.wall_distances = NULL;
	if (parsing(argc, argv, &game))
		return (1);
	game.mlx =  mlx_init(game.w_tile * (game.map->screen_width), game.w_tile * (game.map->screen_height), "Cub3d Game", true);
	if (!(game.mlx))
		error_exit(game.map, "mlx initializing failure");
	place_keys_and_door(&game);
	game.won = 0;
	init_textures(&game);
	init_key_animation_frames(&game);
	init_sprites_allocation(&game);
init_sprites_map_scan(&game);

	draw_2d_map(&game);
	draw_player(&game);
	draw_scene_and_rays(&game);
	game.game_time_start = get_time();
	if (game.wall_distances && game.scene_3d)
	{
		for (int i = 0; i < (int)game.scene_3d->width; i++)
			game.wall_distances[i] = 10000.0f;
	}
	render_all_sprites(&game);
	mlx_key_hook(game.mlx, hide_map2d, &game);
	mlx_cursor_hook(game.mlx, mouse_rotate, &game);
	mlx_loop_hook(game.mlx, &move, &game);
	mlx_loop(game.mlx);
	clean_sources(&game);
	mlx_terminate(game.mlx);
	return (0);
}




