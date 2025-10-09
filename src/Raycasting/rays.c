/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:10:16 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/09 19:02:55 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void draw_rays(t_game *game)
{
	if (!game)
		exit(1);
	game->rays = mlx_new_image(game->mlx,  WIDTH * (game->map->screen_width), HEIGHT * (game->map->screen_height));
	if(!game->rays)
		error_exit(NULL, "image initialization failure");
 	dda(game);
	if (mlx_image_to_window(game->mlx, game->rays, 0, 0) < 0) // fix start position
		error_exit(NULL, "image display failure");//edit to free game as well
}

void dda(t_game *game)
{
	uint32_t *pixels;
	int i;
	
	pixels = (uint32_t *)game->rays->pixels;
	ft_memset(pixels, 0, game->rays->width * game->rays->height * sizeof(uint32_t));
	i = 0;
	while(i < WIDTH * (game->map->screen_width))
	{
    	float camera_x = 2 * i / (float)game->rays->width - 1;
    	float an = game->player->angle + atanf(camera_x * tanf(FOV/ 2));
		draw_single_ray(game, an);
		i++;
	}
}

      
/*void draw_single_ray_pixels(t_game *game, float angle, uint32_t *pixels)
{
	float sq_x;
	float sq_y;
	int map_x;
	int map_y;
	
	sq_x = (game->player->x + game->player->img->width / 2.0f);
	sq_y = (game->player->y + game->player->img->height / 2.0f);
	while (1)
	{
        if ((int)sq_x < 0 || (int)sq_y < 0 || (int)sq_x >= (int)game->rays->width \
		|| (int)sq_y >= (int)game->rays->height)
			break;
		pixels[(int)sq_y * game->rays->width + (int)sq_x] = 0xFFCC00CC;
	
       sq_x += cosf(angle) / (abs_max (cos(angle), sin(angle)));
        sq_y += sinf(angle) / (abs_max (cos(angle), sin(angle)));	
		map_x = (int)(sq_x / WIDTH);
		map_y = (int)(sq_y / HEIGHT);
		if (map_y >= 0 && map_y < (int)ft_strlen_d(game->map->map_lines) && \
		map_x >= 0 && map_x < find_max_len(game->map->map_lines) && \
		game->map->map_lines[map_y][map_x] == '1')
			break;
	}
}*/


/* Bresenham line - integer endpoints */
void draw_line_bresenham(mlx_image_t *img,t_ray_pos *x, t_ray_pos *y, uint32_t color)
{
    int sd[4];// [0]-> sx, [1]-> sy [2]-> dx, [3]-> dy
    int err;
	
	if (!img || !x || !y)
		error_exit(NULL, "draw line failure");//edit
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
	err = sd[2] - sd[3];
    while (1)
    {
		if (x->line_start >= 0 && y->line_start >= 0 && \
x->line_start < (int)img->width && y->line_start < (int)img->height)
((uint32_t *)img->pixels)[y->line_start * img->width + x->line_start] = color;
        if (x->line_start == x->line_end && y->line_start == y->line_end)
			break;
      	err += check_acum_err(err, sd, x, y);
    }
}

int check_acum_err(int err, int sd[4], t_ray_pos *x, t_ray_pos *y)
{
	int e2;
	int inc;

	if (!x || !y)
		error_exit(NULL, "draw line failure");//edit
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

void draw_single_ray(t_game *game, float angle)
{
	t_ray_pos x;
	t_ray_pos y;
	float wall_dist;
	if (!game)
		error_exit(NULL, "draw ray failure");//edit
	x.pos = (game->player->x + game->player->img->width / 2.0f) / WIDTH;
	y.pos = (game->player->y + game->player->img->height / 2.0f) / HEIGHT;
	x.map_p = (int)(x.pos);
	y.map_p = (int)(y.pos);	
	if (evaluate_delta_dist(&x, &y, angle) == 1)
		error_exit(game->map, "error during drawing rays");//edit later
	set_dir(angle, &x, &y);
	wall_dist = find_stop_point(game,&x, &y);
    x.line_start = (int)(x.pos * WIDTH);
    y.line_start = (int)(y.pos * HEIGHT);
    x.line_end = (int)((x.pos+ cosf(angle) * wall_dist) * WIDTH);
    y.line_end = (int)((y.pos + sinf(angle) * wall_dist) * HEIGHT);
    draw_line_bresenham(game->rays, &x, &y, 0xFFCC00CC);
 }

void	set_dir(float angle, t_ray_pos *x, t_ray_pos *y)
{
	if (!x || !y)
		error_exit(NULL, "draw line failure");//edit
	if (cosf(angle) < 0)
	{
		x->sign = -1;
		x->walk = (x->pos - x->map_p ) * x->delta_dist;
	}   
	else
	{
		x->sign = 1;
		x->walk = (1.0f + x->map_p   - x->pos) * x->delta_dist;
	}

	if (sinf(angle) < 0)
	{
		y->sign = -1;
		y->walk = (y->pos - y->map_p ) * y->delta_dist;
	}
	else
	{
		y->sign = 1;
		y->walk = (1.0f + y->map_p   - y->pos) * y->delta_dist;
	}	
}

int evaluate_delta_dist(t_ray_pos *x, t_ray_pos *y, float angle)
 {
	if (!x || !y)
		return (1);
	if (cosf(angle) == 0)
		(x->delta_dist) = 1e10f;
	else
		(x->delta_dist) = fabsf(1.0f / cosf(angle));
	if (sinf(angle) == 0)
		(y->delta_dist) = 1e10f;
	else
		(y->delta_dist) = fabsf(1.0f / sinf(angle));
	return (0);
 }
 
 

int evaluate_walk(t_ray_pos *i)
 {
	if (!i)
		return (-1);
	i->walk += i->delta_dist;  
	i->map_p += i->sign;           
	return (0);
 }
 

float	find_stop_point(t_game *game, t_ray_pos *x, t_ray_pos *y)
 {
	float wall_dist;
	int side_dir;
	
	if (!x || !y || !game)
		error_exit(NULL, "draw line failure");//edit
	side_dir = -1;
	while (1)
	{
    	if (x->walk < y->walk)
    	    side_dir = evaluate_walk(x);
    	else
    	{
    	    evaluate_walk(y);
    	    side_dir = 1; // hit a horizontal wall
    	}
		if (side_dir == -1)
			error_exit(game->map, "error during drawing rays");
		if (y->map_p >= 0 && y->map_p < (int)ft_strlen_d(game->map->map_lines) && \
		x->map_p >= 0 && x->map_p < find_max_len(game->map->map_lines) && \
		game->map->map_lines[y->map_p][x->map_p] == '1')
			break;
	}
	if (side_dir == 0)
	    wall_dist = x->walk - x->delta_dist;			
	else
	    wall_dist = y->walk - y->delta_dist;
	return (wall_dist);
 }
 
 
 