/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:08:57 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/31 22:09:28 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	handle_speed_keys(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_2))
	{
		g->player->move_speed += 1;
		printf(CYAN "Player speed: %.1f\n" NC, g->player->move_speed);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_3))
	{
		g->player->move_speed -= 1;
		printf(CYAN "Player speed: %.1f\n" NC, g->player->move_speed);
	}
	if (g->player->move_speed < 1)
		g->player->move_speed = 1;
	if (g->player->move_speed > 2 * g->mini_tile / 3)
		g->player->move_speed = 2 * g->mini_tile / 3;
}

static void	handle_movement_keys(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
	handle_speed_keys(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
		move_forward(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
		move_backward(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		move_left(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		move_right(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		g->player->angle += 0.15;
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		g->player->angle -= 0.15;
}

static void	reset_and_update_scene(t_game *g)
{
	int	i;

	if (g->player->angle < 0)
		g->player->angle += 2 * M_PI;
	else if (g->player->angle > 2 * M_PI)
		g->player->angle -= 2 * M_PI;
	g->player->img->instances[0].x = g->player->x;
	g->player->img->instances[0].y = g->player->y;
	check_key_pickup(g);
	check_door(g);
	i = 0;
	while (i < (int)g->scene_3d->width)
	{
		g->wall_distances[i] = 10000.0f;
		i++;
	}
}

static void	update_game_state(t_game *g)
{
	reset_and_update_scene(g);
	dda(g);
	render_all_sprites(g);
	if (g->won == 1)
	{
		g->game_time_end = get_time();
		printf(GREEN "You finished the game in %ld.%ld s\n" NC,
			(g->game_time_end - g->game_time_start) / 1000, (g->game_time_end
				- g->game_time_start) % 1000);
		mlx_close_window(g->mlx);
		clean_sources(g);
	}
}

void	move(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g || !g->mlx || !g->player || !g->scene_3d || !g->wall_distances)
		return ;
	handle_speed_keys(g);
	handle_movement_keys(g);
	reset_and_update_scene(g);
	update_game_state(g);
}
