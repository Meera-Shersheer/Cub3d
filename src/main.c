/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/21 01:16:41 by mshershe         ###   ########.fr       */
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

void move(void *param)
{ 
    t_game *g;
	float dx;
	float dy;
	
	g = (t_game *)param;
    dx = 0;
	dy = 0;
	g->player->move_speed = 1;
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
    if (mlx_is_key_down(g->mlx, MLX_KEY_W))
		dy -= g->player->move_speed;
    if (mlx_is_key_down(g->mlx, MLX_KEY_S))
		dy += g->player->move_speed;
    if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		dx -= g->player->move_speed;
    if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		dx += g->player->move_speed;
    if (dx != 0 && dy != 0)// diagonal movement normalization so the diagonal movement is not faster than the straight movement
	{ 
        dx *= 0.7071;
        dy *= 0.7071;
    }
    g->player->x += dx;
    g->player->y += dy;
    g->player->img->instances[0].x = g->player->x;
    g->player->img->instances[0].y = g->player->y;
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
	game.mlx =  mlx_init(WIDTH * (game.map->screen_width), HEIGHT * (game.map->screen_height), "Cub3d Game", true);
	if (!(game.mlx))
		error_exit(game.map, "mlx initializing failure");
	draw_player(&game);
	mlx_loop_hook(game.mlx, &move, &game);
	mlx_loop(game.mlx);
	if (game.player)
	{
    	if (game.player->img)
   			mlx_delete_image(game.mlx, game.player->img);
    	free(game.player);
    	game.player = NULL;
	}
	mlx_terminate(game.mlx);// a must to free some leaks caused by mlx 42
	free_map(game.map);
	
	return (0);
}

void color_block (unsigned int color, mlx_image_t *img)
{
	int	i;
	uint32_t *pixels;
	
	i = 0;
	if (!img)
		return;
	pixels = (uint32_t *)img->pixels;
	while (i < (int)(img->width * img->height))
	{
		pixels[i] = color;
		i++;
	}
}


void draw_player(t_game *game)
{
	if (!game)
		exit(1);
	game->player = malloc(sizeof(t_player));
	if(!game->player)
		error_exit(NULL, "malloc failure");//edit to free game as well
	game->player->x = 0;
    game->player->y = 0;
	game->player->img = mlx_new_image(game->mlx, WIDTH / 4, HEIGHT / 4); // fix dimention of the player
	if(!game->player->img)
		error_exit(NULL, "image initialization failure");
	color_block ( 0xFFFFFF00, game->player->img);
	if (mlx_image_to_window(game->mlx, game->player->img, 0, 0) < 0) // fix start position
		error_exit(NULL, "image display failure");//edit to free game as well

}

