/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:08:11 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/06 21:38:12 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	move_forward(t_game *g)
{
	float	dx;
	float	dy;

	dx = cos(g->player->angle) * g->player->move_speed;
	dy = sin(g->player->angle) * g->player->move_speed;
	try_move(g, dx, dy);
}

void	move_backward(t_game *g)
{
	float	dx;
	float	dy;

	dx = -cos(g->player->angle) * g->player->move_speed;
	dy = -sin(g->player->angle) * g->player->move_speed;
	try_move(g, dx, dy);
}

void	move_left(t_game *g)
{
	float	dx;
	float	dy;

	dx = sin(g->player->angle) * g->player->move_speed;
	dy = -cos(g->player->angle) * g->player->move_speed;
	try_move(g, dx, dy);
}

void	move_right(t_game *g)
{
	float	dx;
	float	dy;

	dx = -sin(g->player->angle) * g->player->move_speed;
	dy = cos(g->player->angle) * g->player->move_speed;
	try_move(g, dx, dy);
}

void	handle_additional_keys2(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g || !g->map_2d || !g->player)
		return ;
	if (keydata.key == MLX_KEY_4 && keydata.action == MLX_PRESS)
	{
		g->player->rot_speed += 0.01;
		if (g->player->rot_speed <= 0)
			g->player->rot_speed = 0.01;
		if (g->player->rot_speed > g->mini_tile / 3)
			g->player->rot_speed = g->mini_tile / 3;
		printf(CYAN "Rotation speed: %.2f\n" NC, g->player->rot_speed);
	}
	if (keydata.key == MLX_KEY_5 && keydata.action == MLX_PRESS)
	{
		g->player->rot_speed -= 0.01;
		if (g->player->rot_speed <= 0)
			g->player->rot_speed = 0.01;
		if (g->player->rot_speed > g->mini_tile / 3)
			g->player->rot_speed = g->mini_tile / 3;
		printf(CYAN "Rotation speed: %.2f\n" NC, g->player->rot_speed);
	}
}
