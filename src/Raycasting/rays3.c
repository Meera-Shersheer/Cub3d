/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:59:25 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/05 16:18:26 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	set_dir(t_angle *angle, t_ray_pos *x, t_ray_pos *y)
{
	if (!x || !y || !angle)
		error_exit(NULL, "draw line failure");
	if (angle->cos_angle < 0)
	{
		x->sign = -1;
		x->walk = (x->pos - x->map_p) * x->delta_dist;
	}
	else
	{
		x->sign = 1;
		x->walk = (1.0f + x->map_p - x->pos) * x->delta_dist;
	}
	if (angle->sin_angle < 0)
	{
		y->sign = -1;
		y->walk = (y->pos - y->map_p) * y->delta_dist;
	}
	else
	{
		y->sign = 1;
		y->walk = (1.0f + y->map_p - y->pos) * y->delta_dist;
	}
}

int	evaluate_delta_dist(t_ray_pos *x, t_ray_pos *y, t_angle *angle)
{
	if (!x || !y)
		return (1);
	if (angle->cos_angle == 0)
		(x->delta_dist) = 1e10f;
	else
		(x->delta_dist) = fabsf(1.0f / angle->cos_angle);
	if (angle->sin_angle == 0)
		(y->delta_dist) = 1e10f;
	else
		(y->delta_dist) = fabsf(1.0f / angle->sin_angle);
	return (0);
}

int	evaluate_walk(t_ray_pos *i)
{
	if (!i)
		return (-1);
	i->walk += i->delta_dist;
	i->map_p += i->sign;
	return (0);
}

int	trace_ray_until_hit(t_game *game, t_ray_pos *x, t_ray_pos *y)
{
	int	side_dir;
	char	tile;
	int		max_iterations;

	side_dir = -1;
	max_iterations = 1000;
	while (max_iterations-- > 0)
	{
		if (x->walk < y->walk)
			side_dir = evaluate_walk(x);
		else
		{
			evaluate_walk(y);
			side_dir = 1;
		}
		if (side_dir == -1)
			error_exit2(game, "error during drawing rays");
		if (y->map_p >= 0 && y->map_p < (int)ft_strlen_d(game->map->map_lines)
			&& x->map_p >= 0 && x->map_p < find_max_len(game->map->map_lines))
		{
			tile = game->map->map_lines[y->map_p][x->map_p];
			if (tile == '1' || (tile == 'D' && game->door_open == 0))
			break ;
		}
	}
	if (max_iterations <= 0)
		error_exit2(game, "Ray tracing exceeded maximum iterations");
	return (side_dir);
}

float	find_stop_point(t_game *game, t_ray_pos *x, t_ray_pos *y)
{
	int		side_dir;
	float	wall_dist;

	if (!x || !y || !game)
		error_exit(NULL, "draw line failure");
	side_dir = trace_ray_until_hit(game, x, y);
	if (side_dir == 0)
		wall_dist = x->walk - x->delta_dist;
	else
		wall_dist = y->walk - y->delta_dist;
	game->hit_side = side_dir;
	return (wall_dist);
}
