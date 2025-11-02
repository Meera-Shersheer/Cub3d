/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:36:49 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/02 21:39:22 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	draw_2d_map(t_game *game)
{
	int	x;
	int	y;

	if (!game)
		exit(1);
	game->map_2d = mlx_new_image(game->mlx, game->mini_tile
			* game->map->screen_width, game->mini_tile
			* game->map->screen_height);
	if (!game->map_2d)
		error_exit2(game, "image initialization failure");
	y = 0;
	while (y < game->map->screen_height)
	{
		x = 0;
		while (x < game->map->screen_width)
			draw_map_tile(game, x++, y);
		y++;
	}
	if (mlx_image_to_window(game->mlx, game->map_2d, 0, 0) < 0)
		error_exit2(game, "image display failure");
}

void	color_square_map2d(t_game *game, unsigned int color, int pixel_x,
		int pixel_y)
{
	uint32_t	*pixels;
	int			i;
	int			j;

	if (!game || !game->map_2d)
		return ;
	pixels = (uint32_t *)game->map_2d->pixels;
	i = 0;
	while (i < game->mini_tile)
	{
		j = 0;
		while (j < game->mini_tile)
		{
			pixels[(i + pixel_x) + (pixel_y + j) * game->map_2d->width] = color;
			j++;
		}
		i++;
	}
}

float	abs_max(float num1, float num2)
{
	float	n1;
	float	n2;

	n1 = fabsf(num1);
	n2 = fabsf(num2);
	if (n1 >= n2)
		return (n1);
	else
		return (n2);
}
