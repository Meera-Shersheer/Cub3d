/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/25 02:04:12 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

 // adjust for comfort

void mouse_rotate(double xpos, double ypos, void *param)
{
    t_game *game;
	double delta_x;
    static double last_x = -1;

	(void) ypos;
	game = (t_game *)param;
    if (last_x == -1)
        last_x = xpos;

    delta_x = xpos - last_x;
    last_x = xpos;
	
    if (delta_x > 0)
	    game->player->angle += 0.05;
    if (delta_x < 0)
		game->player->angle -= 0.05;
	if (game->player->angle < 0)
        game->player->angle += 2 * M_PI;
	else if (game->player->angle > 2 * M_PI)
        game->player->angle -= 2 * M_PI;
}



void move(void *param)
{
    t_game *g;
	
	g = (t_game *)param;
    g->player->move_speed = 5;
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
        g->player->angle += 0.2;
    if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		g->player->angle -= 0.2;
	if (g->player->angle < 0)
        g->player->angle += 2 * M_PI;
	else if (g->player->angle > 2 * M_PI)
        g->player->angle -= 2 * M_PI;
	g->player->img->instances[0].x = g->player->x;
	g->player->img->instances[0].y = g->player->y;
	check_key_pickup(g);
    check_door(g);
	if (g->won == 1)
	{
		mlx_close_window(g->mlx);  // Now safe to close
        return;
	}
	dda(g);
}
	
	
	/*1)test a really huge map and see if we need to resize or give an error
	2)do the textures
	3)write the other bonuses*/
	
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
	//one door and keys (randomly)
	//test the size of window
	place_keys_and_door(&game);
	game.won = 0;
	game.mlx =  mlx_init(W_TILE * (game.map->screen_width), W_TILE * (game.map->screen_height), "Cub3d Game", true);
	if (!(game.mlx))
		error_exit(game.map, "mlx initializing failure");
	init_textures(&game);
	draw_2d_map(&game);
	draw_player(&game);
	draw_scene_and_rays(&game);
	mlx_cursor_hook(game.mlx, mouse_rotate, &game);
	mlx_loop_hook(game.mlx, &move, &game);
	mlx_loop(game.mlx);
	clean_sources(&game);
	mlx_terminate(game.mlx);// a must to free some leaks caused by mlx 42
	return (0);
}


int init_textures(t_game *game)
{
	if (!game)
		exit(1);//edit
	game->textures = malloc(sizeof(t_textures));
	if(!game->textures)
		error_exit(NULL, "malloc failure");//edit to free game as well
	game->textures->tex_no =  mlx_load_png(game->map->north_texture);// add protection and exit 
	game->textures->img_tex_no = mlx_texture_to_image(game->mlx, game->textures->tex_no);//add protection and exit 
	game->textures->tex_we =  mlx_load_png(game->map->west_texture);// add protection and exit 
	game->textures->img_tex_we = mlx_texture_to_image(game->mlx, game->textures->tex_we);//add protection and exit 
	game->textures->tex_ea =  mlx_load_png(game->map->east_texture);// add protection and exit 
	game->textures->img_tex_ea = mlx_texture_to_image(game->mlx, game->textures->tex_ea);//add protection and exit 
	game->textures->tex_so =  mlx_load_png(game->map->south_texture);// add protection and exit 
	game->textures->img_tex_so = mlx_texture_to_image(game->mlx, game->textures->tex_so);//add protection and exit 
	init_door_textures(game);
	init_key_textures(game);
	return (0);
}
int init_door_textures(t_game *g)
{
	
	if (!g || !g->textures)
		error_exit(NULL, "Failure during uploading door/key textures");
	g->textures->door = malloc(sizeof(t_door_textures));
	if (!g->textures->door)
		error_exit2(g, "malloc failure for door textures");
	g->textures->door->tex_door_closed =
mlx_load_png("src_textures/doors/door003.png");
	if (!g->textures->door->tex_door_closed)
		error_exit2(g, "Failed: door closed texture");
	g->textures->door->img_door_closed =
		mlx_texture_to_image(g->mlx, g->textures->door->tex_door_closed);
	if (!g->textures->door->img_door_closed)
		error_exit2(g, "Failed: door closed image");
	g->textures->door->tex_door_semi1 =
		mlx_load_png("src_textures/doors/door001.png");
	if (!g->textures->door->tex_door_semi1)
		error_exit2(g, "Failed: door semi1 texture");
	g->textures->door->img_door_semi1 =
		mlx_texture_to_image(g->mlx, g->textures->door->tex_door_semi1);
	if (!g->textures->door->img_door_semi1)
		error_exit2(g, "Failed: door semi1 image");
	g->textures->door->tex_door_semi2 =
		mlx_load_png("src_textures/doors/door002.png");
	if (!g->textures->door->tex_door_semi2)
		error_exit2(g, "Failed: door semi2 texture");
	g->textures->door->img_door_semi2 =
		mlx_texture_to_image(g->mlx, g->textures->door->tex_door_semi2);
	if (!g->textures->door->img_door_semi2)
		error_exit2(g, "Failed: door semi2 image");
	g->textures->door->tex_door_opened =
		mlx_load_png("src_textures/doors/door000.png");
	if (!g->textures->door->tex_door_opened)
		error_exit2(g, "Failed: door opened texture");
	g->textures->door->img_door_opened =
		mlx_texture_to_image(g->mlx, g->textures->door->tex_door_opened);
	if (!g->textures->door->img_door_opened)
		error_exit2(g, "Failed: door opened image");
	return (0);
}

int	init_key_textures(t_game *g)
{
	if (!g || !g->textures)
		error_exit(NULL, "Failure during uploading door/key textures");
	g->textures->keys = malloc(sizeof(t_key_textures));
	if (!g->textures->keys)
		error_exit2(g, "malloc failure for key textures");
	init_key_textures1(g);
	init_key_textures2(g);
	init_key_textures3(g);
	init_key_textures4(g);
	return (0);
}


void	init_key_textures1(t_game *g)
{
	if (!g || !g->textures  || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
	g->textures->keys->tex_key00 = mlx_load_png("src_textures/keys/key00.png");
	if (!g->textures->keys->tex_key00)
		error_exit2(g, "Failed: key00 texture");
	g->textures->keys->img_key00 =
	mlx_texture_to_image(g->mlx, g->textures->keys->tex_key00);
	if (!g->textures->keys->img_key00)
		error_exit2(g, "Failed: key00 image");
	g->textures->keys->tex_key01 = mlx_load_png("src_textures/keys/key01.png");
	if (!g->textures->keys->tex_key01)
		error_exit2(g, "Failed: key01 texture");
	g->textures->keys->img_key01 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key01);
	if (!g->textures->keys->img_key01)
		error_exit2(g, "Failed: key01 image");
	g->textures->keys->tex_key02 = mlx_load_png("src_textures/keys/key02.png");
	if (!g->textures->keys->tex_key02)
		error_exit2(g, "Failed: key02 texture");
	g->textures->keys->img_key02 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key02);
	if (!g->textures->keys->img_key02)
		error_exit2(g, "Failed: key02 image");
}


void	init_key_textures2(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
	g->textures->keys->tex_key03 = mlx_load_png("src_textures/keys/key03.png");
	if (!g->textures->keys->tex_key03)
		error_exit2(g, "Failed: key03 texture");
	g->textures->keys->img_key03 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key03);
	if (!g->textures->keys->img_key03)
		error_exit2(g, "Failed: key03 image");
	g->textures->keys->tex_key04 = mlx_load_png("src_textures/keys/key04.png");
	if (!g->textures->keys->tex_key04)
		error_exit2(g, "Failed: key04 texture");
	g->textures->keys->img_key04 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key04);
	if (!g->textures->keys->img_key04)
		error_exit2(g, "Failed: key04 image");
	g->textures->keys->tex_key05 = mlx_load_png("src_textures/keys/key05.png");
	if (!g->textures->keys->tex_key05)
		error_exit2(g, "Failed: key05 texture");
	g->textures->keys->img_key05 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key05);
	if (!g->textures->keys->img_key05)
		error_exit2(g, "Failed: key05 image");
}

void	init_key_textures3(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
	g->textures->keys->tex_key06 = mlx_load_png("src_textures/keys/key06.png");
	if (!g->textures->keys->tex_key06)
		error_exit2(g, "Failed: key06 texture");
	g->textures->keys->img_key06 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key06);
	if (!g->textures->keys->img_key06)
		error_exit2(g, "Failed: key06 image");
	g->textures->keys->tex_key07 = mlx_load_png("src_textures/keys/key07.png");
	if (!g->textures->keys->tex_key07)
		error_exit2(g, "Failed: key07 texture");
	g->textures->keys->img_key07 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key07);
	if (!g->textures->keys->img_key07)
		error_exit2(g, "Failed: key07 image");
	g->textures->keys->tex_key08 = mlx_load_png("src_textures/keys/key08.png");
	if (!g->textures->keys->tex_key08)
		error_exit2(g, "Failed: key08 texture");
	g->textures->keys->img_key08 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key08);
	if (!g->textures->keys->img_key08)
		error_exit2(g, "Failed: key08 image");
}
void	init_key_textures4(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
	g->textures->keys->tex_key09 = mlx_load_png("src_textures/keys/key09.png");
	if (!g->textures->keys->tex_key09)
		error_exit2(g, "Failed: key09 texture");
	g->textures->keys->img_key09 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key09);
	if (!g->textures->keys->img_key09)
		error_exit2(g, "Failed: key09 image");
	g->textures->keys->tex_key10 = mlx_load_png("src_textures/keys/key10.png");
	if (!g->textures->keys->tex_key10)
		error_exit2(g, "Failed: key010 texture");
	g->textures->keys->img_key10 =
		mlx_texture_to_image(g->mlx, g->textures->keys->tex_key10);
	if (!g->textures->keys->img_key10)
		error_exit2(g, "Failed: key10 image");
}