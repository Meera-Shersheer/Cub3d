/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 21:58:01 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/03 21:10:07 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"	

void	hide_map2d(mlx_key_data_t keydata, void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g || !g->map_2d || !g->player || !g->player->img || !g->rays)
		return ;
	if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
	{
		if (g->map_2d->instances[0].enabled == true)
		{
			g->map_2d->instances[0].enabled = false;
			g->player->img->instances[0].enabled = false;
			g->rays->instances[0].enabled = false;
			puts(CYAN "Now, the minimap is hidden to make appear press '1'" NC);
		}
		else if (g->map_2d->instances[0].enabled == false)
		{
			g->map_2d->instances[0].enabled = true;
			g->player->img->instances[0].enabled = true;
			g->rays->instances[0].enabled = true;
			puts(CYAN "To hide the minimap press '1'" NC);
		}
	}
}

void	mouse_rotate(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	delta_x;

	(void)ypos;
	game = (t_game *)param;
	if (!game || !game->player)
		return ;
	if (game->mouse_last_x < 0)
	{
		game->mouse_last_x = xpos;
		return ;
	}
	delta_x = xpos - game->mouse_last_x;
	game->mouse_last_x = xpos;
	if (delta_x > 0)
		game->player->angle += 0.05;
	if (delta_x < 0)
		game->player->angle -= 0.05;
	if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
	else if (game->player->angle > 2 * M_PI)
		game->player->angle -= 2 * M_PI;
}
