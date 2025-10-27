/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/27 19:11:08 by mshershe         ###   ########.fr       */
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
	for (int i = 0; i < (int)g->scene_3d->width; i++)
    	g->wall_distances[i] = 10000.0f;  // Reset each frame
	dda(g);
	render_all_sprites(g);
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
	init_sprites(&game);
	draw_2d_map(&game);
	draw_player(&game);
	draw_scene_and_rays(&game);
	render_all_sprites(&game);
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

void init_sprites(t_game *game)
{
	int	i;
	int	j;
	
	if (!game)
		error_exit2(game , "failure during sprite initialization");
	game->sprites = malloc(sizeof(t_sprite_list));
	if (!game->sprites)
		error_exit2(game , "failure during sprite initialization");
	game->sprites->sprites = malloc(sizeof(t_sprite *)  * game->total_keys);
	if (!game->sprites->sprites)
		error_exit2(game , "failure during sprite initialization");
	i = 0;
	game->sprites->count = 0;
	//print_map(game->map);
	while (game->map->map_lines[i])
	{
		j = 0;
		while (game->map->map_lines[i][j])
		{
			if (game->map->map_lines[i][j] == 'K')
				add_key_sprite(game, j , i);
			j++;
		}
		i++;
	}
}

void add_key_sprite(t_game *game, int map_x, int map_y)
{
	t_sprite	*sprite;
	sprite = malloc(sizeof(t_sprite));
	if (!sprite)
		error_exit2(game , "failure during sprite initialization");
	sprite->map_tile_x = map_x;
	sprite->map_tile_y = map_y;
	sprite->x = (map_x + 0.5f) * MINI_TILE;	// Center of tile in world coords
	sprite->y = (map_y + 0.5f) * MINI_TILE;	// Center of tile in world coords
	sprite->img = game->textures->keys->img_key00;
	sprite->collected = 0;
	game->sprites->sprites[game->sprites->count] = sprite;
	game->sprites->count++;
}

void update_sprite_distances(t_game *game)
{
	int i;
	float dx;
	float dy;
	float angle_diff;
	float screen_x_calc;
	float raw_dist;

	i = 0;
	while (i < game->sprites->count)
	{
		if (game->sprites->sprites[i]->collected == 0)
		{
			dx = game->sprites->sprites[i]->x - (game->player->x + game->player->img->width / 2.0f);
			dy = game->sprites->sprites[i]->y - (game->player->y + game->player->img->height / 2.0f);
			raw_dist = sqrtf(dx * dx + dy * dy); // shortest line -> Pythagorean  theorem
			angle_diff = atan2f(dy, dx) - game->player->angle;
			while (angle_diff > M_PI)
				angle_diff -= 2 * M_PI;
			while (angle_diff < -M_PI)
				angle_diff += 2 * M_PI;
			game->sprites->sprites[i]->dist = raw_dist;
			screen_x_calc = (game->scene_3d->width / 2.0f) + (angle_diff * game->scene_3d->width) / FOV;
			if (angle_diff > (FOV / 2.0f) || angle_diff < -(FOV / 2.0f))
			{
				// Sprite is behind/outside view, mark as off-screen
				game->sprites->sprites[i]->screen_x = -10000;
			}
			else
			{
				if (screen_x_calc < -500)
					screen_x_calc = -500;
				if (screen_x_calc > game->scene_3d->width + 500)
					screen_x_calc = game->scene_3d->width + 500;
				
				game->sprites->sprites[i]->screen_x = (int)screen_x_calc;
			// printf("Sprite %d: pos=(%.1f,%.1f) dist=%.2f angle_diff=%.2f screen_x=%d\n",
				    //    i, game->sprites->sprites[i]->x, game->sprites->sprites[i]->y,
				    //    game->sprites->sprites[i]->dist, angle_diff, 
				    //    game->sprites->sprites[i]->screen_x);
			}
		}
		i++;
	}
}

int get_sprite_height(t_game *game, t_sprite *sprite)
{
	int	sprite_height;

	if (sprite->dist < 0.1f)
		sprite->dist = 0.1f;
	sprite_height = (int)(game->scene_3d->height / sprite->dist);
	return (sprite_height);
}

void draw_sprite(t_game *game, t_sprite *sprite)
{
	int			sprite_height;
	int			sprite_width;
	int			draw_start_x;
	int			draw_start_y;
	int			draw_end_x;
	int			draw_end_y;
	int			i;
	int			j;
	uint32_t	*pixels;
	uint32_t	color;
	int			pixels_drawn = 0;

	if (!sprite->img || sprite->collected == 1)
		return ;
	if (!game->wall_distances || !game->scene_3d || !game->scene_3d->pixels)
		return;
	if (sprite->screen_x < -500 || sprite->screen_x > (int)game->scene_3d->width + 500)
    {
			return;  // Skip rendering off-screen sprites
	}
	pixels = (uint32_t *)game->scene_3d->pixels;
	//get ratios
	sprite_height = get_sprite_height(game, sprite);
	sprite_width = (sprite->img->width * sprite_height) / sprite->img->height;
	if (sprite_height <= 0 || sprite_width <= 0)
	{
		return;
	}
	// Center sprite vertically and horizontally
	draw_start_y = (game->scene_3d->height / 2) - (sprite_height / 2);
	draw_start_x = sprite->screen_x - (sprite_width / 2);
	draw_end_y = draw_start_y + sprite_height;
	draw_end_x = draw_start_x + sprite_width;
	
		   
	// Clamp to screen bounds
	if (draw_start_y < 0)
		draw_start_y = 0;
	if (draw_end_y >= (int)game->scene_3d->height)
		draw_end_y = game->scene_3d->height - 1;
	if (draw_start_x < 0)
		draw_start_x = 0;
	if (draw_end_x >= (int)game->scene_3d->width)
		draw_end_x = game->scene_3d->width - 1;
	if (draw_start_x > draw_end_x || draw_start_y > draw_end_y)
		return;	
	i = draw_start_y;
	while (i <= draw_end_y)
	{
		j = draw_start_x;
		while (j <= draw_end_x)
		{
			if (j >= 0 && j < (int)game->scene_3d->width)
			{
				printf("sprite_dist:%f , wall j: %f\n", sprite->dist, game->wall_distances[j]  * MINI_TILE);
				if (sprite->dist < game->wall_distances[j] * MINI_TILE)
				{
					
				// Only draw if sprite is CLOSER than wall in this column
					color = 0xFFCC00CC;
					// color = get_sprite_texture(sprite, 
					 //	(float)(j - draw_start_x) / sprite_width,
				 	//(float)(i - draw_start_y) / sprite_height);
					
					// Only draw non-transparent pixels
					if ((color & 0xFF) != 0)
					{
						pixels[i * game->scene_3d->width + j] = color;
						 printf("Total pixels drawn: %d\n", ++pixels_drawn);
					}
				}
			}
			j++;
		}
		i++;
	}

}


uint32_t get_sprite_texture(t_sprite *sprite, float u, float v)
{
	int		tex_x;
	int		tex_y;
	int		tex_index;
	uint8_t	*p;
	uint8_t	a;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;

	tex_x = (int)(u * sprite->img->width);
	tex_y = (int)(v * sprite->img->height);
	
	// Clamp to texture bounds
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)sprite->img->width)
		tex_x = sprite->img->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)sprite->img->height)
		tex_y = sprite->img->height - 1;
	
	tex_index = (tex_y * sprite->img->width + tex_x) * 4;
	p = sprite->img->pixels;
	a = p[tex_index];
	b = p[tex_index + 1];
	g = p[tex_index + 2];
	r = p[tex_index + 3];
	
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void render_all_sprites(t_game *game)
{
	int	i;

	if (!game->sprites)
		return ;

	// Update distances from player
	update_sprite_distances(game);
	
	// Sort by distance (farthest first)
	//sort_sprites(game);
	
	// Draw all sprites
	i = 0;
	while (i < game->sprites->count)
	{
		draw_sprite(game, game->sprites->sprites[i]);
		i++;
	}
}


// int compare_sprites(const void *a, const void *b)
// {
// 	t_sprite	*sprite_a = *(t_sprite **)a;
// 	t_sprite	*sprite_b = *(t_sprite **)b;

// 	if (sprite_a->dist > sprite_b->dist)
// 		return (-1);
// 	if (sprite_a->dist < sprite_b->dist)
// 		return (1);
// 	return (0);
// }


// void sort_sprites(t_game *game)
// {
// 	qsort(game->sprites->sprites, game->sprites->count, 
// 		  sizeof(t_sprite *), compare_sprites);
// }


