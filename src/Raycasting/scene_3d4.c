/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3d4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:09:56 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/31 18:12:25 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static int	prepare_tex_index(t_tex_info *tex)
{
	int	tex_y;
	int	tex_index;

	if (!tex->tex_pos || !tex->img_tex)
		return (-1);
	tex_y = (int)(*tex->tex_pos);
	*tex->tex_pos += tex->step;
	tex_index = get_tex_index(tex->img_tex, tex->tex_x, tex_y);
	return (tex_index);
}

static uint32_t	read_tex_pixel(mlx_image_t *img_tex, int tex_index)
{
	uint8_t	*p;
	uint8_t	a;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;

	if (!img_tex || tex_index == -1)
		return (0xFF00FFFF);
	p = img_tex->pixels;
	a = p[tex_index];
	b = p[tex_index + 1];
	g = p[tex_index + 2];
	r = p[tex_index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

uint32_t	get_texture_color(t_game *game, t_tex_info *tex)
{
	uint32_t	color;
	uint8_t		a;
	int			tex_index;

	if (!game || !game->textures || !tex)
		return (0xFF00FFFF);
	tex_index = prepare_tex_index(tex);
	color = read_tex_pixel(tex->img_tex, tex_index);
	a = color & 0xFF;
	if (is_door_transparent(game, tex->img_tex, a))
	{
		if (tex->screen_y < 2 * (int)game->scene_3d->height / 3)
			return (game->map->c_color.color);
		else
			return (game->map->f_color.color);
	}
	return (color);
}

void	color_3d_floor_cielling(t_game *game, int col, int draw_start,
		int draw_end)
{
	int			i;
	uint32_t	*pixels;

	pixels = (uint32_t *)game->scene_3d->pixels;
	i = 0;
	while (i < draw_start)
	{
		pixels[i * game->scene_3d->width + col] = game->map->c_color.color;
		i++;
	}
	i = draw_end + 1;
	while (i < (int)game->scene_3d->height)
	{
		pixels[i * game->scene_3d->width + col] = game->map->f_color.color;
		i++;
	}
}

float	eval_real_wall_dist(t_game *game, t_angle *angle, t_ray_pos *x,
		t_ray_pos *y)
{
	float	perp_wall_dist;
	float	angle_diff;

	if (game->hit_side == 0)
		perp_wall_dist = (x->map_p - x->pos + (1 - x->sign) / 2.0f)
			/ angle->cos_angle;
	else
		perp_wall_dist = (y->map_p - y->pos + (1 - y->sign) / 2.0f)
			/ angle->sin_angle;
	angle_diff = angle->angle - game->player->angle;
	perp_wall_dist = perp_wall_dist * cosf(angle_diff);
	if (perp_wall_dist < 0.1f)
		perp_wall_dist = 0.1f;
	return (perp_wall_dist);
}
