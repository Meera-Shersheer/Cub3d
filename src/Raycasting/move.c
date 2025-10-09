/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:08:11 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/09 19:02:51 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

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
