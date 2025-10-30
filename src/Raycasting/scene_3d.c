/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:45:48 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/30 02:18:15 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void draw_single_col(t_game *game, float angle, int col)
{
	t_ray_pos x;
	t_ray_pos y;
	t_ray_dic rays;
	t_angle an;
	
	an.cos_angle = cosf(angle);
	an.sin_angle = sinf(angle);
	an.angle = angle;
	if (!game || !game->player)
		error_exit(NULL, "draw ray failure");//edit
	x.pos = (game->player->x + game->player->img->width / 2.0f) / game->mini_tile;
	y.pos = (game->player->y + game->player->img->height / 2.0f) / game->mini_tile;
	x.map_p = (int)(x.pos);
	y.map_p = (int)(y.pos);	
	if (evaluate_delta_dist(&x, &y, &an) == 1)
		error_exit(game->map, "error during drawing rays");//edit later
	set_dir(&an, &x, &y);
	find_stop_point(game,&x, &y);
    rays.x = &x;
	rays.y = &y;
	color_3d_scene(game, col, &an, &rays);
}

int eval_wall_height(t_game *game,t_angle *angle, t_ray_dic *rays, int col)
{
    float perp_wall_dist;
    float scale;
    int wall_height;
		
	if (!game || !angle || !rays || ! game->wall_distances)
		error_exit2(game, "error during evaluating wall heights");
    scale = 1.1f;
    perp_wall_dist = eval_real_wall_dist(game, angle, rays->x, rays->y);
	if (perp_wall_dist < game->wall_distances[col])
    	game->wall_distances[col] = perp_wall_dist;
	wall_height = (int)(game->scene_3d->height / (perp_wall_dist * scale));
	return (wall_height);
}

int eval_tex_x(t_game *game, t_angle *angle, t_ray_dic *rays, mlx_image_t *img_tex)
{
	float wallX;
	int tex_x;

	if (!game || !rays || !img_tex)
		exit(2); // edit later
	if (game->hit_side == 0)
		wallX = rays->y->pos + (rays->x->walk - rays->x->delta_dist) * angle->sin_angle;
	else
		wallX = rays->x->pos + (rays->y->walk - rays->y->delta_dist) * angle->cos_angle;
	wallX = wallX - floorf(wallX);
	tex_x = (int)(wallX * img_tex->width);
	if ((game->hit_side == 0 && rays->x->sign < 0) || \
	(game->hit_side == 1 && rays->y->sign > 0))
		tex_x = img_tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)img_tex->width)
		tex_x = img_tex->width - 1;		
	return (tex_x);
}

// Step 4: draw the column
void color_3d_scene(t_game *game, int col, t_angle *angle, t_ray_dic *rays)
{
	t_wall_draw wall;
    int i;
	float step;
	float tex_pos;
	uint32_t *pixels;
	mlx_image_t *img_tex;

	if (!game || !game->scene_3d || !rays)
	{
		printf("ERROR: color_3d_scene null pointer!\n");
		return;
	}
	pixels = (uint32_t *)game->scene_3d->pixels;
	wall.wall_height = eval_wall_height(game, angle, rays, col);
	img_tex = get_wall_texture(game, rays->x, rays->y);
	if (!img_tex)
	{
		printf("ERROR: img_tex is NULL! Direction issue?\n");
		return;
	}
	wall.tex_x =  eval_tex_x(game, angle, rays, img_tex);
	wall.draw_start = (game->scene_3d->height / 2) - (wall.wall_height / 2);
    wall.draw_end = wall.draw_start + wall.wall_height;
	if (wall.draw_start < 0)
		wall.draw_start = 0;
	if (wall.draw_end >= (int)game->scene_3d->height)
		wall.draw_end = game->scene_3d->height - 1;
	color_3d_floor_cielling(game, col, wall.draw_start, wall.draw_end);
	i = wall.draw_start;
	step = (float)img_tex->height / wall.wall_height;
	tex_pos = (wall.draw_start - game->scene_3d->height / 2 + wall.wall_height / 2) * step;
	while (i <= wall.draw_end)
    {
		pixels[i * game->scene_3d->width + col] = 
            get_texture_color(game, &tex_pos, step, wall.tex_x, img_tex, i);
        i++;
    } 
}

mlx_image_t *get_wall_texture(t_game *game, t_ray_pos *x, t_ray_pos *y)
{
    int direction;
    int tile_x;
    int tile_y;

	if (!game || !game->textures || !x || !y)
	{
		printf("ERROR: get_wall_texture null pointer!\n");
		return (NULL);
	}
	tile_x = x->map_p;
	tile_y = y->map_p;
	if (tile_y < 0 || tile_y >= (int)ft_strlen_d(game->map->map_lines) || \
tile_x < 0 || tile_x >= (int)ft_strlen(game->map->map_lines[tile_y]))
		return (NULL);

	if (game->map->map_lines[tile_y][tile_x] == 'D')
	{
		if (!game->textures->door)
			printf("ERROR: DOOR textures is NULL!\n");
		if (game->door_open == 0)
			return (game->textures->door->img_door_closed);
		else
			return (game->textures->door->img_door_opened);
	}
    direction = get_wall_direction(game, x, y); 
    if (direction == NORTH)
	{
		if (!game->textures->img_tex_no)
			printf("ERROR: NORTH texture is NULL!\n");
		return (game->textures->img_tex_no);
	}
	else if (direction == SOUTH)
	{
		if (!game->textures->img_tex_so)
			printf("ERROR: SOUTH texture is NULL!\n");
		return (game->textures->img_tex_so);
	}
	else if (direction == EAST)
	{
		if (!game->textures->img_tex_ea)
			printf("ERROR: EAST texture is NULL!\n");
		return (game->textures->img_tex_ea);
	}
	else if (direction == WEST)
	{
		if (!game->textures->img_tex_we)
			printf("ERROR: WEST texture is NULL!\n");
		return (game->textures->img_tex_we);
	}
	return (NULL);
}
int get_wall_direction(t_game *game, t_ray_pos *x, t_ray_pos *y)
{
	if (!game || !x || !y)
    {
        printf("ERROR: get_wall_direction null pointer!\n");
        return (OTHER);  // Default fallback
    }
    if (game->hit_side == 0)  // Hit vertical wall (NS orientation)
    {
        // Vertical walls face East or West
        if (x->sign > 0)
            return (EAST);   // Ray going right → hits WEST face of wall
        else
            return (WEST);   // Ray going left → hits EAST face of wall
    }
    else  // Hit horizontal wall (EW orientation)
    {
        // Horizontal walls face North or South
        if (y->sign > 0)
            return (SOUTH);  // Ray going down → hits NORTH face of wall
        else
            return (NORTH);  // Ray going up → hits SOUTH face of wall
    }
}

uint32_t get_texture_color(t_game *game, float *tex_pos, float step, int tex_x, mlx_image_t *img_tex, int screen_y)
{
	uint32_t color;
	uint8_t *p;
	int tex_y;
	int tex_index;
	int max_index;
	
	if (!tex_pos || !game || !game->textures || !img_tex)
			return (0xFF00FFFF);
	tex_y = (int)(*tex_pos);
    *tex_pos += step;	
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)img_tex->height)
		tex_y = img_tex->height - 1;
	tex_index = (tex_y * img_tex->width + tex_x) * 4;
	max_index = img_tex->width * img_tex->height * 4;
	if (tex_index < 0 || tex_index + 3 >= max_index)
		return (0xFF00FFFF);
    p = img_tex->pixels;
    uint8_t a = p[tex_index];
    uint8_t b = p[tex_index + 1];
    uint8_t g = p[tex_index + 2];
    uint8_t r = p[tex_index + 3]; 
	if (a == 0 && (img_tex == game->textures->door->img_door_closed || \
img_tex == game->textures->door->img_door_opened || \
img_tex == game->textures->door->img_door_semi1 || \
img_tex == game->textures->door->img_door_semi2))
	{
		
		if (screen_y < 2 * (int)game->scene_3d->height / 3)
			color = game->map->c_color.color;
		else
			color = game->map->f_color.color;
		return (color);
	}
	   
    color = (r << 24) | (g << 16) | (b << 8) | a;
	return (color);
}

void color_3d_floor_cielling(t_game *game, int col, int draw_start,  int draw_end)
{
    int i;
	uint32_t *pixels;
	
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

float eval_real_wall_dist(t_game *game, t_angle *angle, t_ray_pos *x, t_ray_pos *y)
{
	float perp_wall_dist;
    float angle_diff;
	
	if (game->hit_side == 0)
	    perp_wall_dist = (x->map_p - x->pos + (1 - x->sign) / 2.0f) / angle->cos_angle;
	else
	    perp_wall_dist = (y->map_p - y->pos + (1 - y->sign) / 2.0f) / angle->sin_angle;
	angle_diff = angle->angle - game->player->angle;
	perp_wall_dist = perp_wall_dist * cosf(angle_diff);
	if (perp_wall_dist < 0.1f)
    	perp_wall_dist = 0.1f;
	return (perp_wall_dist);
}

