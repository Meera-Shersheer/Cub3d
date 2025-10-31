/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:27:00 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/31 14:07:58 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

mlx_image_t	*load_textures(t_game *game, char *tex_path)
{
	mlx_texture_t	*temp;
	mlx_image_t		*img;

	if (!tex_path)
		return (NULL);
	temp = mlx_load_png(tex_path);
	if (!temp)
		error_exit2(game, "Texture loading failure");
	img = mlx_texture_to_image(game->mlx, temp);
	if (!img)
		error_exit2(game, "Image loading failure");
	mlx_delete_texture(temp);
	return (img);
}

void	init_key_textures_part1(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
	g->textures->keys->img_key00 = load_textures(g,
			"src_textures/keys/key00.png");
	if (!g->textures->keys->img_key00)
		error_exit2(g, "Failed: key00 image");
	g->textures->keys->img_key01 = load_textures(g,
			"src_textures/keys/key01.png");
	if (!g->textures->keys->img_key01)
		error_exit2(g, "Failed: key01 image");
	g->textures->keys->img_key02 = load_textures(g,
			"src_textures/keys/key02.png");
	if (!g->textures->keys->img_key02)
		error_exit2(g, "Failed: key02 image");
	g->textures->keys->img_key03 = load_textures(g,
			"src_textures/keys/key03.png");
	if (!g->textures->keys->img_key03)
		error_exit2(g, "Failed: key03 image");
}

void	init_key_textures_part2(t_game *g)
{
	g->textures->keys->img_key04 = load_textures(g,
			"src_textures/keys/key04.png");
	if (!g->textures->keys->img_key04)
		error_exit2(g, "Failed: key04 image");
	g->textures->keys->img_key05 = load_textures(g,
			"src_textures/keys/key05.png");
	if (!g->textures->keys->img_key05)
		error_exit2(g, "Failed: key05 image");
	g->textures->keys->img_key06 = load_textures(g,
			"src_textures/keys/key06.png");
	if (!g->textures->keys->img_key06)
		error_exit2(g, "Failed: key06 image");
}

void	init_key_textures_part3(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
	g->textures->keys->img_key07 = load_textures(g,
			"src_textures/keys/key07.png");
	if (!g->textures->keys->img_key07)
		error_exit2(g, "Failed: key07 image");
	g->textures->keys->img_key08 = load_textures(g,
			"src_textures/keys/key08.png");
	if (!g->textures->keys->img_key08)
		error_exit2(g, "Failed: key08 image");
	g->textures->keys->img_key09 = load_textures(g,
			"src_textures/keys/key09.png");
	if (!g->textures->keys->img_key09)
		error_exit2(g, "Failed: key09 image");
	g->textures->keys->img_key10 = load_textures(g,
			"src_textures/keys/key10.png");
	if (!g->textures->keys->img_key10)
		error_exit2(g, "Failed: key10 image");
}
