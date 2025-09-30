/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:58:16 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/30 20:18:16 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	game->player->img = mlx_new_image(game->mlx, WIDTH / 3, HEIGHT / 3); // fix dimention of the player
	if(!game->player->img)
		error_exit(NULL, "image initialization failure");
	game->player->x = get_player_x_pos(game->map->map_lines) * WIDTH 
                + (WIDTH - game->player->img->width) / 2;
	game->player->y = get_player_y_pos(game->map->map_lines) * HEIGHT 
                + (HEIGHT - game->player->img->height) / 2;
	game->player->angle = - M_PI / 2;
	color_block ( 0xFF0055CC, game->player->img);
	if (mlx_image_to_window(game->mlx, game->player->img,  game->player->x, \
		game->player->y) < 0) // fix start position
		error_exit(NULL, "image display failure");//edit to free game as well

}


void draw_2d_map(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (!game)
		exit(1);
	game->map_2d = mlx_new_image(game->mlx, WIDTH * (game->map->screen_width), HEIGHT * (game->map->screen_height));
	if(!game->map_2d)
		error_exit(NULL, "image initialization failure");
	while(y < game->map->screen_height)
	{
		x = 0;
		while(x < game->map->screen_width)
		{
			if (game->map->map_lines[y][x] == '1')
				color_square (0xFF230C06, game->map_2d, x * WIDTH, y * HEIGHT);
			else if (game->map->map_lines[y][x] == ' ')
				color_square (0xFF363636 , game->map_2d, x * WIDTH, y * HEIGHT);
			else 
				color_square (0xFFF3C5B9, game->map_2d, x * WIDTH, y * HEIGHT);
			x++;
		}	
		y++;
	}
	if (mlx_image_to_window(game->mlx, game->map_2d, 0, 0) < 0) // fix start position
		error_exit(NULL, "image display failure");//edit to free game as well
}

void color_square (unsigned int color, mlx_image_t *img, int pixel_x, int pixel_y)
{
	uint32_t *pixels;
	int i;
	int j;
	
	i = 0;
	j = 0;
	if (!img)
		return;
	pixels = (uint32_t *)img->pixels;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
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
	uint32_t *pixels = (uint32_t *)game->rays->pixels;
	ft_memset(pixels, 0, game->rays->width * game->rays->height * sizeof(uint32_t));
    
	float  	step;
	float	x_inc;
	float	y_inc;
	int map_x;
	int map_y;
	float x;
	float y;
	float i;

	i = 0;
	while(i < WIDTH * (game->map->screen_width))
	{
    // 1) convert column position to camera space (-1 to +1)
    float camera_x = 2 * i / (float)game->rays->width - 1;

    // 2) compute the ray angle for this column
    float an = game->player->angle + atanf(camera_x * tanf((M_PI / 3) / 2));

		step = abs_max (cos(an), sin(an));
		x_inc = cos(an) / step;
		y_inc = sin(an) / step;
		x = game->player->x + game->player->img->width / 2.0f;
		y = game->player->y + game->player->img->height / 2.0f;
		while (1)
		{
			int xi = (int)x;
    	    int yi = (int)y;
		
    	    if (xi < 0 || yi < 0 || xi >= (int)game->rays->width || yi >= (int)game->rays->height)
				break;
			pixels[yi * game->rays->width + xi] = 0xFFCC00CC;
		
    	    x += x_inc;
    	    y += y_inc;
			
			map_x = (int)(x / WIDTH);
			map_y = (int)(y / HEIGHT);
			if (map_y >= 0 && map_y < (int)ft_strlen_d(game->map->map_lines) && map_x >= 0 && \
			map_x < find_max_len(game->map->map_lines) && game->map->map_lines[map_y][map_x] == '1')
				break;
		}
		i++;;
	}
}
