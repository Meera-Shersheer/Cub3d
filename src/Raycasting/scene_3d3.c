/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3d3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:05:28 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/02 21:45:49 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	get_wall_direction(t_game *game, t_ray_pos *x, t_ray_pos *y)
{
	if (!game || !x || !y)
	{
		printf("ERROR: get_wall_direction null pointer!\n");
		return (OTHER);
	}
	if (game->hit_side == 0)
	{
		if (x->sign > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (y->sign > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

int	get_tex_index(mlx_image_t *img_tex, int tex_x, int tex_y)
{
	int	tex_index;
	int	max_index;

	if (!img_tex)
		return (-1);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)img_tex->height)
		tex_y = img_tex->height - 1;
	tex_index = (tex_y * img_tex->width + tex_x) * 4;
	max_index = img_tex->width * img_tex->height * 4;
	if (tex_index < 0 || tex_index + 3 >= max_index)
		return (-1);
	return (tex_index);
}

int	is_door_transparent(t_game *game, mlx_image_t *img_tex, uint8_t alpha)
{
	if (alpha != 0)
		return (0);
	if (img_tex == game->textures->door->img_door_closed
		|| img_tex == game->textures->door->img_door_opened)
		return (1);
	return (0);
}
