/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:17:22 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/08 17:51:58 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	init_textures(t_game *game)
{
	if (!game)
		error_exit3(game, "init textures failure");
	game->textures = malloc(sizeof(t_textures));
	if (!game->textures)
		error_exit3(game, "malloc failure");
	ft_bzero(game->textures, sizeof(t_textures));
	game->textures->img_tex_no = load_textures(game, game->map->north_texture);
	game->textures->img_tex_we = load_textures(game, game->map->west_texture);
	game->textures->img_tex_ea = load_textures(game, game->map->east_texture);
	game->textures->img_tex_so = load_textures(game, game->map->south_texture);
	if (!game->textures->img_tex_no || !game->textures->img_tex_we
		|| !game->textures->img_tex_ea || !game->textures->img_tex_so)
		error_exit3(game, "Texture loading failure");
	init_door_textures(game);
	init_key_textures(game);
	return (0);
}

int	init_door_textures(t_game *g)
{
	if (!g || !g->textures)
		error_exit(NULL, "Failure during uploading door/key textures");
	g->textures->door = malloc(sizeof(t_door_textures));
	if (!g->textures->door)
		error_exit3(g, "malloc failure for door textures");
	ft_bzero(g->textures->door, sizeof(t_door_textures));
	g->textures->door->img_door_closed = load_textures(g,
			"src_textures/doors/door003.png");
	if (!g->textures->door->img_door_closed)
		error_exit3(g, "Failed: door closed image");
	g->textures->door->img_door_opened = load_textures(g,
			"src_textures/doors/door000.png");
	if (!g->textures->door->img_door_opened)
		error_exit3(g, "Failed: door opened image");
	return (0);
}

int	init_key_textures(t_game *g)
{
	if (!g || !g->textures)
		error_exit3(g, "Failure during uploading door/key textures");
	g->textures->keys = malloc(sizeof(t_key_textures));
	if (!g->textures->keys)
		error_exit3(g, "malloc failure for key textures");
	ft_bzero(g->textures->keys, sizeof(t_key_textures));
	init_key_textures_part1(g);
	init_key_textures_part2(g);
	init_key_textures_part3(g);
	init_key_textures_part4(g);
	init_key_textures_part5(g);
	init_key_textures_part6(g);
	return (0);
}

void	init_sprites_allocation(t_game *game)
{
	if (!game)
		error_exit3(game, "failure during sprite initialization");
	game->sprites = malloc(sizeof(t_sprite_list));
	if (!game->sprites)
		error_exit3(game, "failure during sprite initialization");
	ft_bzero(game->sprites, sizeof(t_sprite_list));
	game->sprites->sprites = malloc(sizeof(t_sprite *) * game->total_keys);
	if (!game->sprites->sprites)
		error_exit3(game, "failure during sprite initialization");
	ft_bzero(game->sprites->sprites, sizeof(t_sprite *));
	game->sprites->count = 0;
}

void	init_sprites_map_scan(t_game *game)
{
	int	i;
	int	j;

	if (!game || !game->sprites || !game->map || !game->map->map_lines)
		error_exit3(game, "failure during sprite initialization");
	i = 0;
	while (game->map->map_lines[i])
	{
		j = 0;
		while (game->map->map_lines[i][j])
		{
			if (game->map->map_lines[i][j] == 'K')
				add_key_sprite(game, j, i);
			j++;
		}
		i++;
	}
}
