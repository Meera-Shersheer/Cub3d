/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:00:14 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/31 14:00:15 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	init_key_textures_part4(t_game *g)
{
	g->textures->keys->img_key11 = load_textures(g,
			"src_textures/keys/key11.png");
	if (!g->textures->keys->img_key11)
		error_exit2(g, "Failed: key11 image");
	g->textures->keys->img_key12 = load_textures(g,
			"src_textures/keys/key12.png");
	if (!g->textures->keys->img_key12)
		error_exit2(g, "Failed: key12 image");
	g->textures->keys->img_key13 = load_textures(g,
			"src_textures/keys/key13.png");
	if (!g->textures->keys->img_key13)
		error_exit2(g, "Failed: key13 image");
}

void	init_key_textures_part5(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
	g->textures->keys->img_key14 = load_textures(g,
			"src_textures/keys/key14.png");
	if (!g->textures->keys->img_key14)
		error_exit2(g, "Failed: key14 image");
	g->textures->keys->img_key15 = load_textures(g,
			"src_textures/keys/key15.png");
	if (!g->textures->keys->img_key15)
		error_exit2(g, "Failed: key15 image");
	g->textures->keys->img_key16 = load_textures(g,
			"src_textures/keys/key16.png");
	if (!g->textures->keys->img_key16)
		error_exit2(g, "Failed: key16 image");
}

void	init_key_textures_part6(t_game *g)
{
	g->textures->keys->img_key17 = load_textures(g,
			"src_textures/keys/key17.png");
	if (!g->textures->keys->img_key17)
		error_exit2(g, "Failed: key17 image");
	g->textures->keys->img_key18 = load_textures(g,
			"src_textures/keys/key18.png");
	if (!g->textures->keys->img_key18)
		error_exit2(g, "Failed: key18 image");
	g->textures->keys->img_key19 = load_textures(g,
			"src_textures/keys/key19.png");
	if (!g->textures->keys->img_key19)
		error_exit2(g, "Failed: key19 image");
	g->textures->keys->img_key20 = load_textures(g,
			"src_textures/keys/key20.png");
	if (!g->textures->keys->img_key20)
		error_exit2(g, "Failed: key20 image");
}
