/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:45:48 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/14 18:49:00 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"


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

    // Step 2: wall projection height
	wall_height = (int)(game->scene_3d->height/ corrected_dist);
    // Step 3: draw start & end
	color_3d_scene(game, wall_height, col);
 }

 void color_3d_scene(t_game *game, int wall_height, int col)
 {
	int draw_start;
    int draw_end;
	uint32_t *pixels;
	int y = 0;
	
	draw_start = (game->scene_3d->height / 2) - (wall_height / 2);
	draw_end = draw_start + wall_height;
	
    if (draw_start < 0)
		draw_start = 0;
    if (draw_end >= (int)game->scene_3d->height)
		draw_end = game->scene_3d->height - 1;

    // Step 4: draw the column
    pixels = (uint32_t *)game->scene_3d->pixels;
	y = 0;
    while (y < (int)game->scene_3d->height)
    {
        uint32_t color;
        if (y < draw_start)
            color = game->map->c_color.color;
        else if (y > draw_end)
            color = game->map->f_color.color;
        else
            color = 0xFF228B22;

        pixels[y * game->scene_3d->width + col] = color;
		y++ ;
    }
 }
 
