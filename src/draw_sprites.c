/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 23:20:28 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/31 23:20:46 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// 1. Initialize sprite draw info
static int	init_sprite_draw(t_game *game, t_sprite *sprite, int *w, int *h)
{
	const float	sprite_scale = 5.0f;

	if (!game || !sprite || !sprite->img || sprite->collected == 1)
		return (0);
	if (!game->wall_distances || !game->scene_3d || !game->scene_3d->pixels)
		return (0);
	*h = get_sprite_height(game, sprite) * sprite_scale;
	*w = (sprite->img->width * (*h)) / sprite->img->height;
	if (*w <= 0 || *h <= 0)
		return (0);
	return (1);
}

// 2. Draw a single column of the sprite
static uint32_t	get_sprite_pixel_color(t_game *game, t_sprite *sprite, int x,
		int y)
{
	int			sprite_width;
	int			start_y;
	uint32_t	color;

	sprite_width = (sprite->img->width * get_sprite_height(game, sprite) * 5.0f)
		/ sprite->img->height;
	start_y = (game->scene_3d->height / 2) - (sprite_width * sprite->img->height
			/ sprite->img->width / 5);
	color = get_sprite_texture(sprite, (float)(x - (sprite->screen_x
					- sprite_width / 2)) / sprite_width, (float)(y - start_y)
			/ (sprite_width * sprite->img->height / sprite->img->width / 5));
	if ((color & 0xFF) == 0)
		return (0);
	if (x < 0 || x >= (int)game->scene_3d->width || y < 0
		|| y >= (int)game->scene_3d->height)
		return (0);
	if (game->wall_distances[x] <= 0 || sprite->dist >= game->wall_distances[x]
		* game->mini_tile)
		return (0);
	return (color);
}

static void	draw_sprite_col(t_game *game, t_sprite *sprite, int x,
		int sprite_height)
{
	int			y;
	uint32_t	*pixels;
	int			start_y;
	uint32_t	color;

	pixels = (uint32_t *)game->scene_3d->pixels;
	start_y = (game->scene_3d->height / 2) - (sprite_height / 2);
	y = start_y;
	while (y <= start_y + sprite_height)
	{
		color = get_sprite_pixel_color(game, sprite, x, y);
		if (color != 0)
			pixels[y * game->scene_3d->width + x] = color;
		y++;
	}
}

// 3. Loop over sprite columns
static void	draw_sprite_loop(t_game *game, t_sprite *sprite, int sprite_width,
		int sprite_height)
{
	int	x;
	int	start_x;
	int	end_x;

	start_x = sprite->screen_x - (sprite_width / 2);
	end_x = start_x + sprite_width;
	x = start_x;
	while (x <= end_x)
	{
		draw_sprite_col(game, sprite, x, sprite_height);
		x++;
	}
}

// 4. Main draw_sprite function
void	draw_sprite(t_game *game, t_sprite *sprite)
{
	int	sprite_width;
	int	sprite_height;

	if (!init_sprite_draw(game, sprite, &sprite_width, &sprite_height))
		return ;
	if (sprite->screen_x < -500 || sprite->screen_x > (int)game->scene_3d->width
		+ 500)
		return ;
	draw_sprite_loop(game, sprite, sprite_width, sprite_height);
}
