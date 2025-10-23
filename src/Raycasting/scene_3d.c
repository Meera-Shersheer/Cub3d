/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:45:48 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/23 10:58:35 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void draw_single_col(t_game *game, float angle, int col)
{
	t_ray_pos x;
	t_ray_pos y;
	t_ray_dic rays;
	
	if (!game || !game->player)
		error_exit(NULL, "draw ray failure");//edit
	x.pos = (game->player->x + game->player->img->width / 2.0f) / MINI_TILE;
	y.pos = (game->player->y + game->player->img->height / 2.0f) / MINI_TILE;
	x.map_p = (int)(x.pos);
	y.map_p = (int)(y.pos);	
	if (evaluate_delta_dist(&x, &y, angle) == 1)
		error_exit(game->map, "error during drawing rays");//edit later
	set_dir(angle, &x, &y);
	find_stop_point(game,&x, &y);
    rays.x = &x;
	rays.y = &y;
	color_3d_scene(game, col, angle, &rays);
}

int eval_wall_height(t_game *game, float angle, t_ray_pos *x, t_ray_pos *y)
{
    float perp_wall_dist;
    float scale;
    int wall_height;

    scale = 0.7f;
    perp_wall_dist = eval_real_wall_dist(game, angle, x, y);
    wall_height = (int)(game->scene_3d->height / (perp_wall_dist * scale));
    return (wall_height);
}

int eval_tex_x(t_game *game, float angle, t_ray_dic *rays, mlx_image_t *img_tex)
{
	float wallX;
	int tex_x;

	if (!game || !rays || !img_tex)
		exit(2); // edit later
	if (game->hit_side == 0)
		wallX = rays->y->pos + (rays->x->walk - rays->x->delta_dist) * sinf(angle);
	else
		wallX = rays->x->pos + (rays->y->walk - rays->y->delta_dist) * cosf(angle);
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
void color_3d_scene(t_game *game, int col,float angle, t_ray_dic *rays)
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
	wall.wall_height = eval_wall_height(game, angle, rays->x, rays->y);
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
            get_texture_color(game, &tex_pos, step, wall.tex_x, img_tex);
        i++;
    } 
}

mlx_image_t *get_wall_texture(t_game *game, t_ray_pos *x, t_ray_pos *y)
{
    int direction;
    
	if (!game || !game->textures || !x || !y)
	{
		printf("ERROR: get_wall_texture null pointer!\n");
		return (NULL);
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
	// else
	// 	return (game->textures->img_tex_door);

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

uint32_t get_texture_color(t_game *game, float *tex_pos, float step, int tex_x, mlx_image_t *img_tex)
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

float eval_real_wall_dist(t_game *game, float angle, t_ray_pos *x, t_ray_pos *y)
{
	float perp_wall_dist;
	
	if (game->hit_side == 0)
	    perp_wall_dist = (x->map_p - x->pos + (1 - x->sign) / 2.0f) / cosf(angle);
	else
	    perp_wall_dist = (y->map_p - y->pos + (1 - y->sign) / 2.0f) / sinf(angle);
	if (perp_wall_dist < 0.1f)
    	perp_wall_dist = 0.1f;
	return (perp_wall_dist);
}
/*if (game->hit_side == 1)
    color = (color >> 1) & 0x7F7F7F7F;
*/

// void init_scene_3d(t_game *game)
// {
// 	if (!game)
// 		exit(1);
// 	game->scene_3d = mlx_new_image(game->mlx, W_TILE * (game->map->screen_width), W_TILE * (game->map->screen_height));
// 	if(!game->scene_3d)
// 		error_exit(NULL, "image initialization failure");
// 	dda_3d(game);
// 	//color_block (0xFF228B22, game->scene_3d); //TEST
// 	if (mlx_image_to_window(game->mlx, game->scene_3d, 0, 0) < 0) // fix start position
// 		error_exit(NULL, "image display failure");//edit to free game as well
// 	mlx_set_instance_depth(&game->scene_3d->instances[0],-1);
// }

// void dda_3d(t_game *game)
// /* an2 is another way to calculate the angles of the rays other than the camera and tan*/
// {
// 	uint32_t *pixels;
// 	float camera_x;
// 	float an;
// 	int i;
	
// 	if (!game || !game->scene_3d || !game->player)
// 		error_exit(NULL, "draw ray failure");//edit
// 	pixels = (uint32_t *)game->scene_3d->pixels;
// 	ft_memset(pixels, 0, game->scene_3d->width * game->scene_3d->height * sizeof(uint32_t));
// 	i = 0;
// 	while(i <  (int)game->scene_3d->width )
// 	{
//     	camera_x = 2 * i / (float)game->scene_3d->width - 1;
//     	an = game->player->angle + atanf(camera_x * tanf(FOV/ 2));
// 		draw_single_col(game, an, i);
// 		i++;
// 	}
// }
