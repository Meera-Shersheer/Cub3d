/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/12 16:10:31 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"




	/* If we PRESS the 'J' key, print "Hello" on terminal.
	if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		puts("Hello ");

	// If we RELEASE the 'K' key, print "World" on terminal.
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
		puts("World");

	// If we HOLD the 'L' key, print "!" on terminal.
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
		puts("!");

		*/


void hide_map2d(mlx_key_data_t keydata, void *param)
{
    t_game *g;
	
	g = (t_game *)param;
    if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		if (g->map_2d->instances[0].enabled == true )
		{
			g->map_2d->instances[0].enabled = false;
			g->player->img->instances[0].enabled = false;
			g->rays->instances[0].enabled = false;
			puts("Now, the minimap is hidden to make appear press '1'\n");
		}
		else if (g->map_2d->instances[0].enabled == false )
		{
			g->map_2d->instances[0].enabled = true;
			g->player->img->instances[0].enabled = true;
			g->rays->instances[0].enabled = true;
			puts("To hide the minimap press '1'\n");
		}
	}
}		
void move(void *param)
{
    t_game *g;
	
	g = (t_game *)param;
    g->player->move_speed = 1;
	mlx_key_hook(g->mlx, hide_map2d, param);
    if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(g->mlx);
    if (mlx_is_key_down(g->mlx, MLX_KEY_W))
        move_forward(g);
    if (mlx_is_key_down(g->mlx, MLX_KEY_S))
        move_backward(g);
    if (mlx_is_key_down(g->mlx, MLX_KEY_A))
        move_left(g);
    if (mlx_is_key_down(g->mlx, MLX_KEY_D))
        move_right(g);
    if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
        g->player->angle += 0.05;
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
        g->player->angle -= 0.05;
    if (g->player->angle < 0)
        g->player->angle += 2 * M_PI;
    else if (g->player->angle > 2 * M_PI)
        g->player->angle -= 2 * M_PI;
    g->player->img->instances[0].x = g->player->x;
    g->player->img->instances[0].y = g->player->y;
    dda(g);
}




 /*To test leaks: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=mlx.supp ./cub3D map*/
int	main(int argc, char *argv[])
{
	t_game game;
	
	ft_bzero(&game, sizeof(game));
	game.map = malloc(sizeof(t_map));
	if(!game.map)
		error_exit(NULL, "malloc failure");
	if (parsing(argc, argv, &game))
		return (1);
	game.mlx =  mlx_init(W_TILE * (game.map->screen_width), W_TILE * (game.map->screen_height), "Cub3d Game", true);
	if (!(game.mlx))
		error_exit(game.map, "mlx initializing failure");
	draw_2d_map(&game);
	draw_player(&game);
	draw_rays(&game);
	mlx_loop_hook(game.mlx, &move, &game);
	mlx_loop(game.mlx);
	if (game.player)
	{
    	if (game.player->img)
   			mlx_delete_image(game.mlx, game.player->img);
    	free(game.player);
    	game.player = NULL;
	}
    if (game.map_2d)
   		mlx_delete_image(game.mlx, game.map_2d);
	mlx_terminate(game.mlx);// a must to free some leaks caused by mlx 42
	free_map(game.map);
	
	return (0);
}
