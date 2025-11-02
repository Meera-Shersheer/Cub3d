/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 01:11:29 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/03 01:18:08 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	calc_sprite_draw(t_game *game, t_sprite *sprite, t_sprite_draw *sd)
{
	float	sprite_scale;

	sprite_scale = 5.0f;
	sd->height = get_sprite_height(game, sprite) * sprite_scale;
	sd->width = (sprite->img->width * sd->height) / sprite->img->height;
	sd->start_y = (game->scene_3d->height / 2) - (sd->height / 2);
	sd->start_x = sprite->screen_x - (sd->width / 2);
	sd->end_y = sd->start_y + sd->height;
	sd->end_x = sd->start_x + sd->width;
	if (sd->start_y < 0)
		sd->start_y = 0;
	if (sd->end_y >= (int)game->scene_3d->height)
		sd->end_y = game->scene_3d->height - 1;
	if (sd->start_x < 0)
		sd->start_x = 0;
	if (sd->end_x >= (int)game->scene_3d->width)
		sd->end_x = game->scene_3d->width - 1;
}

static int	init_sprite_draw(t_game *game, t_sprite *sprite, t_sprite_draw *sd)
{
	if (!is_sprite_drawable(game, sprite))
		return (0);
	calc_sprite_draw(game, sprite, sd);
	if (sd->height <= 0 || sd->width <= 0)
		return (0);
	return (sd->start_x <= sd->end_x && sd->start_y <= sd->end_y);
}

static int	get_sprite_pixel_color(t_game *game, t_sprite *sprite,
		t_sprite_draw *sd, uint32_t *color)
{
	if (game->wall_distances[sd->cur_x] > 0
		&& sprite->dist < game->wall_distances[sd->cur_x] * game->mini_tile)
	{
		*color = get_sprite_texture(sprite, (float)(sd->cur_x - sd->start_x)
				/ sd->width, (float)(sd->cur_y - sd->start_y) / sd->height);
		if ((*color & 0xFF) != 0)
			return (1);
	}
	return (0);
}

static void	render_sprite_pixels(t_game *game, t_sprite *sprite,
		t_sprite_draw *sd)
{
	int			pixel_index;
	uint32_t	*pixels;
	uint32_t	color;

	pixels = (uint32_t *)game->scene_3d->pixels;
	sd->cur_y = sd->start_y;
	while (sd->cur_y <= sd->end_y)
	{
		sd->cur_x = sd->start_x;
		while (sd->cur_x <= sd->end_x)
		{
			if (get_sprite_pixel_color(game, sprite, sd, &color))
			{
				pixel_index = sd->cur_y * game->scene_3d->width + sd->cur_x;
				pixels[pixel_index] = color;
			}
			sd->cur_x++;
		}
		sd->cur_y++;
	}
}

void	draw_sprite(t_game *game, t_sprite *sprite)
{
	t_sprite_draw	sd;

	if (!init_sprite_draw(game, sprite, &sd))
		return ;
	render_sprite_pixels(game, sprite, &sd);
}
