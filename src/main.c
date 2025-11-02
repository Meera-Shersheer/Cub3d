/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/02 20:19:14 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"	
	/*To test leaks: valgrind --leak-check=full --show-leak-kinds=all 
	--track-origins=yes --suppressions=mlx.supp ./cub3D map*/

int	main(int argc, char *argv[])
{
	t_game	game;
	int		i;

	init_game(argc, argv, &game);
	draw_2d_map(&game);
	draw_player(&game);
	draw_scene_and_rays(&game);
	game.game_time_start = get_time();
	if (game.wall_distances && game.scene_3d)
	{
		i = 0;
		while (i < (int)game.scene_3d->width)
			game.wall_distances[i++] = 10000.0f;
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

void update_sprite_distances(t_game *game)
{
	int i;
	float dx;
	float dy;
	float angle_diff;
	float screen_x_calc;
	float raw_dist;

	if (!game || !game->sprites || !game->player || !game->player->img || !game->scene_3d)
		return;
	i = 0;
	while (i < game->sprites->count)
	{
		if (!game->sprites->sprites[i])
		{
			i++;
			continue;
		}
		
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
				game->sprites->sprites[i]->screen_x = -10000;
			}
			else
			{
				if (screen_x_calc < -500)
					screen_x_calc = -500;
				if (screen_x_calc > game->scene_3d->width + 500)
					screen_x_calc = game->scene_3d->width + 500;			
				game->sprites->sprites[i]->screen_x = (int)screen_x_calc;
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

	const float SPRITE_SCALE = 5.0f;
	if (!game || !sprite || !sprite->img || sprite->collected == 1)
		return ;
	if (!game->wall_distances || !game->scene_3d || !game->scene_3d->pixels)
		return;
	if (sprite->screen_x < -500 || sprite->screen_x > (int)game->scene_3d->width + 500)
			return;
	pixels = (uint32_t *)game->scene_3d->pixels;
	sprite_height = get_sprite_height(game, sprite) * SPRITE_SCALE;
	sprite_width = (sprite->img->width * sprite_height) / sprite->img->height;
	if (sprite_height <= 0 || sprite_width <= 0)
		return;
	draw_start_y = (game->scene_3d->height / 2) - (sprite_height / 2);
	draw_start_x = sprite->screen_x - (sprite_width / 2);
	draw_end_y = draw_start_y + sprite_height;
	draw_end_x = draw_start_x + sprite_width;
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
			if (j >= 0 && j < (int)game->scene_3d->width && \
				i >= 0 && i < (int)game->scene_3d->height)
			{
				if (j < (int)game->scene_3d->width && 
					game->wall_distances[j] > 0 && sprite->dist < game->wall_distances[j] * game->mini_tile)
				{
					 color = get_sprite_texture(sprite, \
						(float)(j - draw_start_x) / sprite_width,	\
						(float)(i - draw_start_y) / sprite_height);
					if ((color & 0xFF) != 0)
						{
							int pixel_index = i * game->scene_3d->width + j;
							if (pixel_index >= 0 && pixel_index < (int)(game->scene_3d->width * game->scene_3d->height))
								pixels[pixel_index] = color;
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

	if (!sprite || !sprite->img || !sprite->img->pixels)
		return (0);
	if (sprite->img->width == 0 || sprite->img->height == 0)
		return (0);
	tex_x = (int)(u * sprite->img->width);
	tex_y = (int)(v * sprite->img->height);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)sprite->img->width)
		tex_x = sprite->img->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)sprite->img->height)
		tex_y = sprite->img->height - 1;
	tex_index = (tex_y * sprite->img->width + tex_x) * 4;
	if (tex_index < 0 || tex_index + 3 >= (int)(sprite->img->width * sprite->img->height * 4))
		return (0);
	p = sprite->img->pixels;
	a = p[tex_index];
	b = p[tex_index + 1];
	g = p[tex_index + 2];
	r = p[tex_index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}




void sort_sprites(t_game *game)
{
	int i;
	int j;
	t_sprite *temp;
	
	if (!game || !game->sprites || game->sprites->count <= 1)
		return;
	
	i = 0;
	while (i < game->sprites->count - 1)
	{
		j = 0;
		while (j < game->sprites->count - i - 1)
		{
			if (game->sprites->sprites[j] && game->sprites->sprites[j + 1])
			{
				if (game->sprites->sprites[j]->dist < game->sprites->sprites[j + 1]->dist)
				{
					temp = game->sprites->sprites[j];
					game->sprites->sprites[j] = game->sprites->sprites[j + 1];
					game->sprites->sprites[j + 1] = temp;
				}
			}
			j++;
		}
		i++;
	}
}


