/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:09:32 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/31 19:09:38 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	draw_single_col(t_game *game, float angle, int col)
{
	t_ray_pos	x;
	t_ray_pos	y;
	t_ray_dic	rays;
	t_angle		an;

	an.cos_angle = cosf(angle);
	an.sin_angle = sinf(angle);
	an.angle = angle;
	if (!game || !game->player)
		error_exit(NULL, "draw ray failure");
	x.pos = (game->player->x + game->player->img->width / 2.0f)
		/ game->mini_tile;
	y.pos = (game->player->y + game->player->img->height / 2.0f)
		/ game->mini_tile;
	x.map_p = (int)(x.pos);
	y.map_p = (int)(y.pos);
	if (evaluate_delta_dist(&x, &y, &an) == 1)
		error_exit(game->map, "error during drawing rays");
	set_dir(&an, &x, &y);
	find_stop_point(game, &x, &y);
	rays.x = &x;
	rays.y = &y;
	color_3d_scene(game, col, &an, &rays);
}

int	eval_wall_height(t_game *game, t_angle *angle, t_ray_dic *rays, int col)
{
	float	perp_wall_dist;
	float	scale;
	int		wall_height;

	if (!game || !angle || !rays || !game->wall_distances)
		error_exit2(game, "error during evaluating wall heights");
	scale = 1.1f;
	perp_wall_dist = eval_real_wall_dist(game, angle, rays->x, rays->y);
	if (perp_wall_dist < game->wall_distances[col])
		game->wall_distances[col] = perp_wall_dist;
	wall_height = (int)(game->scene_3d->height / (perp_wall_dist * scale));
	return (wall_height);
}

int	eval_tex_x(t_game *game, t_angle *angle, t_ray_dic *rays,
		mlx_image_t *img_tex)
{
	float	wall_x;
	int		tex_x;

	if (!game || !rays || !img_tex)
		exit(2);
	if (game->hit_side == 0)
		wall_x = rays->y->pos + (rays->x->walk - rays->x->delta_dist)
			* angle->sin_angle;
	else
		wall_x = rays->x->pos + (rays->y->walk - rays->y->delta_dist)
			* angle->cos_angle;
	wall_x = wall_x - floorf(wall_x);
	tex_x = (int)(wall_x * img_tex->width);
	if ((game->hit_side == 0 && rays->x->sign < 0) || (game->hit_side == 1
			&& rays->y->sign > 0))
		tex_x = img_tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)img_tex->width)
		tex_x = img_tex->width - 1;
	return (tex_x);
}
