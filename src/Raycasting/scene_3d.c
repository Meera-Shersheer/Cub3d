/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:45:48 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/16 19:25:44 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void draw_single_col(t_game *game, float angle, int col)
{
	t_ray_pos x;
	t_ray_pos y;
	float wall_dist;
	float corrected_dist;	
	int wall_height;
	
	if (!game || !game->player)
		error_exit(NULL, "draw ray failure");//edit
	x.pos = (game->player->x + game->player->img->width / 2.0f) / MINI_TILE;
	y.pos = (game->player->y + game->player->img->height / 2.0f) / MINI_TILE;
	x.map_p = (int)(x.pos);
	y.map_p = (int)(y.pos);	
	
	if (evaluate_delta_dist(&x, &y, angle) == 1)
		error_exit(game->map, "error during drawing rays");//edit later
	set_dir(angle, &x, &y);
	wall_dist = find_stop_point(game,&x, &y);
	
	corrected_dist = wall_dist * cosf(angle - game->player->angle);
 // float x_hit = x.pos + (x.map_p - x.pos) + (x.walk - x.delta_dist) * cosf(angle);
   // float y_hit = y.pos + (y.map_p - y.pos) + (y.walk - y.delta_dist) * sinf(angle);


    // Step 2: wall projection height
	wall_height = (int)(game->scene_3d->height/ corrected_dist);
    // Step 3: draw start & end
	 color_3d_scene(game, wall_height, wall_dist,  col, angle, &x, &y);
}

// Step 4: draw the column
void color_3d_scene(t_game *game, int wall_height, float wall_dist, int col,float angle, t_ray_pos *x, t_ray_pos *y)
{
    int draw_start;
    int draw_end;
    float wallX;
    int tex_x;
    int i;
	//float dist;
//	int tex_y;
(void) angle;
(void) wall_dist;
float hitX;
float hitY;

    
    // Clamp to screen boundaries
  
	float perp_wall_dist;
	if (game->hit_side == 0) // vertical wall (X grid line)
	    perp_wall_dist = (x->map_p - x->pos + (1 - x->sign) / 2.0f) / cosf(angle);
	else // horizontal wall (Y grid line)
	    perp_wall_dist = (y->map_p - y->pos + (1 - y->sign) / 2.0f) / sinf(angle);
	if (perp_wall_dist < 0.1f)
    	perp_wall_dist = 0.1f;

	wall_height = (int)(game->scene_3d->height / perp_wall_dist);
	if (game->hit_side == 0)
	{
    	hitX = x->line_end;   // already the exact intersection in world units
    	hitY = y->pos + (x->walk - x->delta_dist) * sin(angle);
	}
	else
	{
   		hitX = x->pos + (y->walk - y->delta_dist) * cos(angle);
    	hitY = y->line_end;
	}
	if (game->hit_side == 0) // vertical wall
    	wallX = hitY - floorf(hitY); // take fractional part of Y
	else // horizontal wall
    	wallX = hitX - floorf(hitX); // take fractional part of X
	
	tex_x = (int)(wallX * game->img_tex->width);
	if ((game->hit_side == 0 && x->sign < 0) ||
    (game->hit_side == 1 && y->sign > 0))
		tex_x = game->img_tex->width - tex_x - 1;

	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)game->img_tex->width)
		tex_x = game->img_tex->width - 1;
		//float tex_pos = (draw_start - game->scene_3d->height / 2 + wall_height / 2) * step;
	draw_start = (game->scene_3d->height / 2) - (wall_height / 2);
    draw_end = draw_start + wall_height;
	if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= (int)game->scene_3d->height)
		draw_end = game->scene_3d->height - 1;

	for (i = 0; i < draw_start; ++i)
        mlx_put_pixel(game->scene_3d, col, i, game->map->c_color.color);
	i = draw_start;
	float step = (float)game->img_tex->height / wall_height;
	float tex_pos = (draw_start - game->scene_3d->height / 2 + wall_height / 2) * step;
	while (i <= draw_end)
    {
        uint32_t color;

	//	int pixel_on_wall = i - draw_start;               /* 0..wall_height-1 */
      //  int tex_y = (int)(pixel_on_wall * step);
	    int tex_y = (int)tex_pos;
    	tex_pos += step;	
	 	if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)game->img_tex->height)
			tex_y = game->img_tex->height - 1;
		
		// Get the pixel from texture (RGBA format = 4 bytes per pixel)
		int tex_index = (tex_y * game->img_tex->width + tex_x) * 4;
        uint8_t *p = game->img_tex->pixels;
        int max_index = game->img_tex->width * game->img_tex->height * 4;
        if (tex_index < 0 || tex_index + 3 >= max_index)
        {
            /* debugging: draw magenta so you can see invalid read */
            mlx_put_pixel(game->scene_3d, col, i, 0xFF00FFFF);
            continue;
        }
		
		  // Read pixel (ABGR format from your PNG)
        uint8_t r = p[tex_index];
        uint8_t g = p[tex_index + 1];
        uint8_t b = p[tex_index + 2];
        uint8_t a = p[tex_index + 3];
        
        color = (r << 24) | (g << 16) | (b << 8) | a;
    
		mlx_put_pixel(game->scene_3d, col, i, color);
        i++;
    }
	for (i = draw_end + 1; i < (int)game->scene_3d->height; ++i)
        mlx_put_pixel(game->scene_3d, col, i, game->map->f_color.color);
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
