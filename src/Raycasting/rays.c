/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:10:16 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/30 16:05:06 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"


void draw_scene_and_rays(t_game *game)
{
	if (!game)
		exit(1);
	game->rays = mlx_new_image(game->mlx,  game->mini_tile * (game->map->screen_width), game->mini_tile * (game->map->screen_height));
	game->scene_3d = mlx_new_image(game->mlx, W_TILE * (game->map->screen_width), W_TILE * (game->map->screen_height));
	if(!game->rays || !game->scene_3d)
		error_exit(NULL, "image initialization failure");
	game->wall_distances = malloc(sizeof(float) * game->scene_3d->width);
	if (!game->wall_distances)
		error_exit(game->map, "malloc failure for wall_distances");
	for (int i = 0; i < (int)game->scene_3d->width; i++)
    	game->wall_distances[i] = 10000.0f;	
 	dda(game);
	if (mlx_image_to_window(game->mlx, game->rays, 0, 0) < 0) // fix start position
		error_exit(NULL, "image display failure");//edit to free game as well
	if (mlx_image_to_window(game->mlx, game->scene_3d, 0, 0) < 0) // fix start position
		error_exit(NULL, "image display failure");//edit to free game as well
	mlx_set_instance_depth(&game->scene_3d->instances[0],-1);
}

/* an2 is another way to calculate the angles of the rays other than the camera and tan*/
//an2 = game->player->angle - (FOV / 2);
//an2 += FOV / game->rays->width;
void	dda(t_game *game)
{
	float camera_x;
	float an;
	int i;
	
	//if (!game || !game->scene_3d || !game->player)
	if (!game || !game->scene_3d || !game->player || !game->rays)
		error_exit(NULL, "cast ray failure");
	ft_memset((uint32_t *)game->rays->pixels , 0, game->rays->width * 
	game->rays->height * sizeof(uint32_t));
	i = 0;
	while(i < (int)game->scene_3d->width)
	{
		camera_x = 2 * i / (float)game->scene_3d->width - 1;
		an = game->player->angle + atanf(camera_x * tanf(FOV/ 2));
		draw_single_col(game, an, i);
		i++;
	}
	i = 0;
	while (i < game->mini_tile * game->map->screen_width)
	{
		camera_x = 2 * i / (float)game->rays->width - 1;
    	an = game->player->angle + atanf(camera_x * tanf(FOV/ 2));
		cast_rays(game, an);
		i++;
	}
}


      
/*void draw_single_ray_pixels(t_game *game, float angle, uint32_t *pixels)
{
	float sq_x;
	float sq_y
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

void cast_rays(t_game *game, float angle)
{
	t_ray_pos x;
	t_ray_pos y;
	t_angle an;
	float wall_dist;
	
	an.cos_angle = cosf(angle);
	an.sin_angle = sinf(angle);
	if (!game  || !game->player)
		error_exit(NULL, "cast ray failure");//edit
	x.pos = (game->player->x + game->player->img->width / 2.0f) / game->mini_tile;
	y.pos = (game->player->y + game->player->img->height / 2.0f) / game->mini_tile;
	x.map_p = (int)(x.pos);
	y.map_p = (int)(y.pos);	
	if (evaluate_delta_dist(&x, &y, &an) == 1)
		error_exit(game->map, "error during drawing rays");//edit later
	set_dir(&an, &x, &y);
	wall_dist = find_stop_point(game,&x, &y);
    x.line_start = (int)(x.pos * game->mini_tile);
    y.line_start = (int)(y.pos * game->mini_tile);
    x.line_end = (int)((x.pos+ an.cos_angle * wall_dist) * game->mini_tile);
    y.line_end = (int)((y.pos + an.sin_angle * wall_dist) * game->mini_tile);
    draw_line_bresenham(game->rays, &x, &y, 0xFF00EE00);
 }

void	set_dir(t_angle *angle, t_ray_pos *x, t_ray_pos *y)
{
	if (!x || !y || !angle)
		error_exit(NULL, "draw line failure");//edit
	if (angle->cos_angle < 0)
	{
		x->sign = -1;
		x->walk = (x->pos - x->map_p ) * x->delta_dist;
	}   
	else
	{
		x->sign = 1;
		x->walk = (1.0f + x->map_p   - x->pos) * x->delta_dist;
	}

	if (angle->sin_angle < 0)
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

int evaluate_delta_dist(t_ray_pos *x, t_ray_pos *y, t_angle *angle)
 {
	if (!x || !y)
		return (1);
	if (angle->cos_angle == 0)
		(x->delta_dist) = 1e10f;
	else
		(x->delta_dist) = fabsf(1.0f / angle->cos_angle);
	if (angle->sin_angle  == 0)
		(y->delta_dist) = 1e10f;
	else
		(y->delta_dist) = fabsf(1.0f / angle->sin_angle );
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
		(game->map->map_lines[y->map_p][x->map_p] == '1' || game->map->map_lines[y->map_p][x->map_p] == 'D'))
			break;
	}
	if (side_dir == 0)
	    wall_dist = x->walk - x->delta_dist;			
	else
	    wall_dist = y->walk - y->delta_dist;
	game->hit_side = side_dir;
	return (wall_dist);
 }
 


 
 
 