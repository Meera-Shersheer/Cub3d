/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:17:22 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/30 21:11:12 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

mlx_image_t *load_textures(t_game *game, char *tex_path)
{
	mlx_texture_t *temp;
	mlx_image_t *img;
	
	if (!tex_path)
		return (NULL);
	temp =  mlx_load_png(tex_path);
	if (!temp)
		error_exit2(game, "Texture loading failure");
	img = mlx_texture_to_image(game->mlx, temp);
	if (!img)
		error_exit2(game, "Image loading failure");
	mlx_delete_texture(temp);
	return (img);
}
int init_textures(t_game *game)
{
	if (!game)
		exit(1);//edit
	game->textures = malloc(sizeof(t_textures));
	if(!game->textures)
		error_exit2(game, "malloc failure");
	game->textures->img_tex_no = load_textures(game, game->map->north_texture);
	game->textures->img_tex_we = load_textures(game, game->map->west_texture);
	game->textures->img_tex_ea = load_textures(game, game->map->east_texture);
	game->textures->img_tex_so = load_textures(game, game->map->south_texture);
	if(!game->textures->img_tex_no || !game->textures->img_tex_we || \
		!game->textures->img_tex_ea  || !game->textures->img_tex_so)
		error_exit2(game, "Texture loading failure");
	init_door_textures(game);
	init_key_textures(game);
	return (0);
}
int init_door_textures(t_game *g)
{
	if (!g || !g->textures)
		error_exit(NULL, "Failure during uploading door/key textures");
	g->textures->door = malloc(sizeof(t_door_textures));
	if (!g->textures->door)
		error_exit2(g, "malloc failure for door textures");
	g->textures->door->img_door_closed = load_textures(g, "src_textures/doors/door003.png");
	if (!g->textures->door->img_door_closed)
		error_exit2(g, "Failed: door closed image");	
	g->textures->door->img_door_opened =  load_textures(g, "src_textures/doors/door000.png");
	if (!g->textures->door->img_door_opened)
		error_exit2(g, "Failed: door opened image");
	return (0);
}

int	init_key_textures(t_game *g)
{
	if (!g || !g->textures)
		error_exit2(g, "Failure during uploading door/key textures");
	g->textures->keys = malloc(sizeof(t_key_textures));
	if (!g->textures->keys)
		error_exit2(g, "malloc failure for key textures");
	init_key_textures1(g);
	init_key_textures2(g);
	init_key_textures3(g);
	return (0);
}

void init_sprites(t_game *game)
{
	int	i;
	int	j;
	
	if (!game)
		error_exit2(game , "failure during sprite initialization");
	game->sprites = malloc(sizeof(t_sprite_list));
	if (!game->sprites)
		error_exit2(game , "failure during sprite initialization");
	ft_bzero(game->sprites, sizeof(t_sprite_list));
	game->sprites->sprites = malloc(sizeof(t_sprite *)  * game->total_keys);
	if (!game->sprites->sprites)
		error_exit2(game , "failure during sprite initialization");
	ft_bzero(game->sprites->sprites, sizeof(t_sprite *));
	i = 0;
	game->sprites->count = 0;
	while (game->map->map_lines[i])
	{
		j = 0;
		while (game->map->map_lines[i][j])
		{
			if (game->map->map_lines[i][j] == 'K')
				add_key_sprite(game, j , i);
			j++;
		}
		i++;
	}
}