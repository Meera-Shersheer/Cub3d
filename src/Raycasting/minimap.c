/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:58:16 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/23 15:38:43 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void color_block (unsigned int color, mlx_image_t *img)
{
	int	i;
	uint32_t *pixels;
	
	i = 0;
	if (!img)
		return;
	pixels = (uint32_t *)img->pixels;
	while (i < (int)(img->width * img->height))
	{
		// if (i < (int)(img->width) * 2)
		// 	pixels[i] = 0xFF000000;
		// else
			pixels[i] = color;
		i++;
	}
}


void draw_player(t_game *game)
{
	if (!game)
		exit(1);
	game->player = malloc(sizeof(t_player));
	if(!game->player)
		error_exit(NULL, "malloc failure");//edit to free game as well
	if(!game->map)
		error_exit(NULL, "map failure");//edit to free game as well
	game->player->img = mlx_new_image(game->mlx, MINI_TILE / 3, MINI_TILE / 3); // fix dimention of the player
	if(!game->player->img)
		error_exit(NULL, "image initialization failure");
	game->player->x = get_player_x_pos(game->map->map_lines) * MINI_TILE 
                + (MINI_TILE - game->player->img->width) / 2;
	game->player->y = get_player_y_pos(game->map->map_lines) * MINI_TILE 
                + (MINI_TILE - game->player->img->height) / 2;
	pick_initial_angle (game);
	color_block (0xFFCC00CC, game->player->img);
	if (mlx_image_to_window(game->mlx, game->player->img,  game->player->x, \
		game->player->y) < 0) // fix start position
		error_exit(NULL, "image display failure");//edit to free game as well

}
void pick_initial_angle (t_game *game)
{
	if (!game)
		exit(1);
	if (game ->map->initial_look_dir == 'N')
		game->player->angle = - M_PI / 2; // north
	else if (game ->map->initial_look_dir == 'S')
		game->player->angle =  M_PI / 2; // south
	else if (game ->map->initial_look_dir == 'W')
		game->player->angle =  M_PI; // west
	else 
		game->player->angle = 0; // east
	
}

void draw_2d_map(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (!game)
		exit(1);
	game->map_2d = mlx_new_image(game->mlx, MINI_TILE * (game->map->screen_width), MINI_TILE * (game->map->screen_height));
	if(!game->map_2d)
		error_exit(NULL, "image initialization failure");
	while(y < game->map->screen_height)
	{
		x = 0;
		while(x < game->map->screen_width)
		{
			if (game->map->map_lines[y][x] == '1')
				color_square_map2d (0xFF230C06, game->map_2d, x * MINI_TILE, y * MINI_TILE);
			else if (game->map->map_lines[y][x] == ' ')
				color_square_map2d (0xFF363636 , game->map_2d, x * MINI_TILE, y * MINI_TILE);
			else if (game->map->map_lines[y][x] == 'K')
			{
    			color_square_map2d(0xFFF3C5B9, game->map_2d, x * MINI_TILE, y * MINI_TILE);
    			draw_key_symbol(game->map_2d, x * MINI_TILE, y * MINI_TILE);
			}
			else if (game->map->map_lines[y][x] == 'D')
			{
    			draw_door_symbol(game->map_2d, x * MINI_TILE, y * MINI_TILE);
			}
			else 
				color_square_map2d (0xFFF3C5B9, game->map_2d, x * MINI_TILE, y * MINI_TILE);
			x++;
		}	
		y++;
	}
	if (mlx_image_to_window(game->mlx, game->map_2d, 0, 0) < 0) // fix start position
		error_exit(NULL, "image display failure");//edit to free game as well
}

void color_square_map2d (unsigned int color, mlx_image_t *img, int pixel_x, int pixel_y)
{
	uint32_t *pixels;
	int i;
	int j;
	
	i = 0;
	j = 0;
	if (!img)
		return;
	pixels = (uint32_t *)img->pixels;
	while (i < MINI_TILE)
	{
		j = 0;
		while (j < MINI_TILE)
		{
			pixels[(i + pixel_x) + (pixel_y + j) * img->width] = color;
			j++;
		}
		i++;
	}
}

float abs_max (float num1, float num2)
{
	float n1;
	float n2;
	
	n1 = fabsf (num1);
	n2 = fabsf (num2);
	if (n1 >= n2)
		return (n1);
	else
		return (n2);
}

