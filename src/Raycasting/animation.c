/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:29:55 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/06 15:26:27 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_key_animation_frames(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		error_exit2(NULL, "Failure during animation setup");
	g->textures->keys->animation_frames[0] = g->textures->keys->img_key00;
	g->textures->keys->animation_frames[1] = g->textures->keys->img_key01;
	g->textures->keys->animation_frames[2] = g->textures->keys->img_key02;
	g->textures->keys->animation_frames[3] = g->textures->keys->img_key03;
	g->textures->keys->animation_frames[4] = g->textures->keys->img_key04;
	g->textures->keys->animation_frames[5] = g->textures->keys->img_key05;
	g->textures->keys->animation_frames[6] = g->textures->keys->img_key06;
	g->textures->keys->animation_frames[7] = g->textures->keys->img_key07;
	g->textures->keys->animation_frames[8] = g->textures->keys->img_key08;
	g->textures->keys->animation_frames[9] = g->textures->keys->img_key09;
	g->textures->keys->animation_frames[10] = g->textures->keys->img_key10;
	g->textures->keys->animation_frames[11] = g->textures->keys->img_key11;
	g->textures->keys->animation_frames[12] = g->textures->keys->img_key12;
	g->textures->keys->animation_frames[13] = g->textures->keys->img_key13;
	g->textures->keys->animation_frames[14] = g->textures->keys->img_key14;
	g->textures->keys->animation_frames[15] = g->textures->keys->img_key15;
	g->textures->keys->animation_frames[16] = g->textures->keys->img_key16;
	g->textures->keys->animation_frames[17] = g->textures->keys->img_key17;
	g->textures->keys->animation_frames[18] = g->textures->keys->img_key18;
	g->textures->keys->animation_frames[19] = g->textures->keys->img_key19;
	g->textures->keys->animation_frames[20] = g->textures->keys->img_key20;
}

void	add_key_sprite(t_game *game, int map_x, int map_y)
{
	t_sprite	*sprite;

	sprite = malloc(sizeof(t_sprite));
	if (!sprite || !game)
		error_exit2(game, "failure during sprite initialization");
	sprite->map_tile_x = map_x;
	sprite->map_tile_y = map_y;
	sprite->x = (map_x + 0.5f) * game->mini_tile;
	sprite->y = (map_y + 0.5f) * game->mini_tile;
	sprite->img = game->textures->keys->img_key01;
	sprite->collected = 0;
	sprite->frame_count = 21;
	sprite->last_update_time = 0;
	sprite->frames = game->textures->keys->animation_frames;
	sprite->img = sprite->frames[0];
	sprite->frame = 0;
	game->sprites->sprites[game->sprites->count] = sprite;
	game->sprites->count++;
}

void	update_sprite_animation(t_sprite *sprite)
{
	long	current_time_ms;
	long	elapsed_ms;

	if (!sprite || !sprite->frames || !sprite->img)
		return ;
	current_time_ms = get_time();
	if (sprite->last_update_time == 0)
		sprite->last_update_time = current_time_ms;
	elapsed_ms = current_time_ms - sprite->last_update_time;
	if (elapsed_ms >= FRAME_DURATION_MS)
	{
		sprite->last_update_time = current_time_ms;
		sprite->frame++;
		if (sprite->frame >= sprite->frame_count)
			sprite->frame = 0;
		if (sprite->frame < 0 || sprite->frame >= sprite->frame_count)
			sprite->frame = 0;
		sprite->img = sprite->frames[sprite->frame];
	}
}

void	update_all_sprites_animation(t_game *game)
{
	int	i;

	if (!game || !game->sprites || !game->sprites->sprites)
		return ;
	i = 0;
	while (i < game->sprites->count)
	{
		if (game->sprites->sprites[i]
			&& game->sprites->sprites[i]->collected == 0)
		{
			update_sprite_animation(game->sprites->sprites[i]);
		}
		i++;
	}
}

void	render_all_sprites(t_game *game)
{
	int		i;

	if (!game || !game->sprites || !game->sprites->sprites)
		return ;
	update_sprite_distances(game);
	sort_sprites(game);
	update_all_sprites_animation(game);
	i = 0;
	while (i < game->sprites->count)
	{
		if (game->sprites->sprites[i])
			draw_sprite(game, game->sprites->sprites[i]);
		i++;
	}
}
