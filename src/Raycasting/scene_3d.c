/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:45:48 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/15 19:04:20 by mshershe         ###   ########.fr       */
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
	float x_hit = game->player->x + wall_dist * cosf(angle);
	float y_hit = game->player->y + wall_dist * sinf(angle);


    // Step 2: wall projection height
	wall_height = (int)(game->scene_3d->height/ corrected_dist);
    // Step 3: draw start & end
	color_3d_scene(game, wall_height,col, x_hit, y_hit);
}

// Step 4: draw the column
void	color_3d_scene(t_game *game, int wall_height, int col, float x_hit, float y_hit)
{
	int draw_start;
    int draw_end;
	uint32_t *pixels;
	  float wallX;
	int y;
	
	draw_start = (game->scene_3d->height / 2) - (wall_height / 2);
	draw_end = draw_start + wall_height;
    if (draw_start < 0)
		draw_start = 0;
    if (draw_end >= (int)game->scene_3d->height)
		draw_end = game->scene_3d->height - 1;
    pixels = (uint32_t *)game->scene_3d->pixels;
	y = 0;
	 // Calculate wallX (texture x-coordinate)
    if (game->hit_side == 0)  // vertical wall (hit x-side)
        wallX = y_hit - floorf(y_hit);
    else                      // horizontal wall (hit y-side)
        wallX = x_hit - floorf(x_hit);
    // Ensure wallX is in [0, 1) range
    if (wallX < 0)
        wallX += 1.0f;
    if (wallX >= 1.0f)
        wallX -= 1.0f;
    // Calculate texture x coordinate (column in texture)
    int tex_x = (int)(wallX * game->texture->width);
    
    // Clamp tex_x to valid range
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= (int)game->texture->width)
        tex_x = game->texture->width - 1;
		
    while (y < (int)game->scene_3d->height)
    {
		uint32_t color;
        if (y < draw_start)
			color = game->map->c_color.color;
        else if (y > draw_end)
			color = game->map->f_color.color;
        else
		{


			 int d = y - draw_start;
            int tex_y = d * game->texture->height / wall_height;
            
            // Clamp tex_y to valid range
            if (tex_y < 0)
                tex_y = 0;
            if (tex_y >= (int)game->texture->height)
                tex_y = game->texture->height - 1;
            
            // Get pixel from texture
            // Assuming RGBA format (4 bytes per pixel)
            int tex_index = (tex_y * game->texture->width + tex_x) * 4;
            uint8_t *p = game->texture->pixels;
            
            // Construct color in correct format (RGBA for MLX42)
            uint8_t r = p[tex_index];
            uint8_t g = p[tex_index + 1];
            uint8_t b = p[tex_index + 2];
            uint8_t a = p[tex_index + 3];
            
            // Pack into uint32_t (format depends on your library)
            // For MLX42: RGBA order
            color = (a << 24) | (r << 16) | (g << 8) | b;
			//0xFF228B22;
        
		}
			pixels[y * game->scene_3d->width + col] = color;
		y++ ;
    }
}




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
