/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:11:12 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/02 20:52:27 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	draw_circle(int radius, t_center center, uint32_t color,
		mlx_image_t *img)
{
	int			i;
	int			j;
	int			px;
	int			py;
	uint32_t	*pixels;

	pixels = (uint32_t *)img->pixels;
	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			if (i * i + j * j <= (radius * radius))
			{
				px = center.center_x + i;
				py = center.center_y + j;
				if (px >= 0 && px < (int)img->width && py >= 0
					&& py < (int)img->height)
					pixels[py * img->width + px] = color;
			}
			j++;
		}
		i++;
	}
}

void	draw_rectangle(t_dimention dim, t_center center, uint32_t color,
		mlx_image_t *img)
{
	int			i;
	int			j;
	uint32_t	*pixels;
	int			px;
	int			py;

	pixels = (uint32_t *)img->pixels;
	i = 0;
	while (i < dim.width)
	{
		j = 0;
		while (j < dim.height)
		{
			px = center.center_x + i;
			py = center.center_y + j;
			if (px >= 0 && px < (int)img->width && py >= 0
				&& py < (int)img->height)
			{
				pixels[py * img->width + px] = color;
			}
			j++;
		}
		i++;
	}
}

void	draw_key_symbol(t_game *game, mlx_image_t *img, int pixel_x,
		int pixel_y)
{
	t_center	center;
	t_dimention	dim;
	int			radius;

	radius = game->mini_tile / 6;
	if (!img || !game)
		return ;
	center.center_x = pixel_x + game->mini_tile / 2;
	center.center_y = pixel_y + game->mini_tile / 2;
	draw_circle(radius, center, 0xFFDD0000, img);
	dim.width = 2 * radius;
	dim.height = radius / 2;
	center.center_x += radius;
	draw_rectangle(dim, center, 0xFFDD0000, img);
}

void	draw_door_symbol(t_game *game, mlx_image_t *img, int px, int py)
{
	uint32_t	door_color;
	uint32_t	knob_color;
	t_dimention	dim;
	t_center	center;

	door_color = 0xFF006600;
	knob_color = 0xFF00FFD7;
	dim.width = game->mini_tile;
	dim.height = game->mini_tile;
	center.center_x = px;
	center.center_y = py;
	draw_rectangle(dim, center, door_color, img);
	center.center_x = px + game->mini_tile - 4;
	center.center_y = py + game->mini_tile / 2;
	draw_circle(2, center, knob_color, img);
}
