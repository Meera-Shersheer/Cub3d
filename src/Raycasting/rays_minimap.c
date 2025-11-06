/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:15:16 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/06 21:51:10 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_line_values(int *sd, t_ray_pos *x, t_ray_pos *y)
{
	sd[2] = abs(x->line_end - x->line_start);
	sd[3] = abs(y->line_end - y->line_start);
	if (x->line_start < x->line_end)
		sd[0] = 1;
	else
		sd[0] = -1;
	if (y->line_start < y->line_end)
		sd[1] = 1;
	else
		sd[1] = -1;
}

void	draw_line_bresenham(mlx_image_t *img, t_ray_pos *x, t_ray_pos *y,
		uint32_t color)
{
	int	sd[4];
	int	err;

	if (!img || !x || !y)
		error_exit(NULL, "draw line failure");
	init_line_values(sd, x, y);
	err = sd[2] - sd[3];
	while (1)
	{
		if (x->line_start >= 0 && y->line_start >= 0
			&& x->line_start < (int)img->width
			&& y->line_start < (int)img->height)
			((uint32_t *)img->pixels)[y->line_start * img->width
				+ x->line_start] = color;
		if (x->line_start == x->line_end && y->line_start == y->line_end)
			break ;
		err += check_acum_err(err, sd, x, y);
	}
}

int	check_acum_err(int err, int sd[4], t_ray_pos *x, t_ray_pos *y)
{
	int	e2;
	int	inc;

	if (!x || !y)
		error_exit(NULL, "draw line failure");
	inc = 0;
	e2 = 2 * err;
	if (e2 >= -sd[3])
	{
		inc += -sd[3];
		x->line_start += sd[0];
	}
	if (e2 <= sd[2])
	{
		inc += sd[2];
		y->line_start += sd[1];
	}
	return (inc);
}

void	cast_rays(t_game *game, float angle)
{
	t_ray_pos	x;
	t_ray_pos	y;
	t_angle		an;
	float		wall_dist;

	an.cos_angle = cosf(angle);
	an.sin_angle = sinf(angle);
	if (!game || !game->player)
		error_exit(NULL, "cast ray failure");
	x.pos = (game->player->x + game->player->img->width / 2.0f) \
/ game->mini_tile;
	y.pos = (game->player->y + game->player->img->height / 2.0f) \
/ game->mini_tile;
	x.map_p = (int)(x.pos);
	y.map_p = (int)(y.pos);
	if (x.map_p < 0 || x.map_p >= find_max_len(game->map->map_lines) \
|| y.map_p < 0 || y.map_p >= (int)ft_strlen_d(game->map->map_lines) \
|| game->map->map_lines[y.map_p][x.map_p] == 'D')
		return ;
	if (evaluate_delta_dist(&x, &y, &an) == 1)
		error_exit(game->map, "error during drawing rays");
	set_dir(&an, &x, &y);
	wall_dist = find_stop_point(game, &x, &y);
	x.line_start = (int)(x.pos * game->mini_tile);
	y.line_start = (int)(y.pos * game->mini_tile);
	x.line_end = (int)((x.pos + an.cos_angle * wall_dist) * game->mini_tile);
	y.line_end = (int)((y.pos + an.sin_angle * wall_dist) * game->mini_tile);
	draw_line_bresenham(game->rays, &x, &y, 0xFF00EE00);
}
