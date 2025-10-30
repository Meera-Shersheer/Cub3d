/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:27:00 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/30 01:36:39 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	init_key_textures1(t_game *g)
{
	if (!g || !g->textures  || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
		
	g->textures->keys->img_key00 = load_textures(g, "src_textures/keys/key00.png");
	if (!g->textures->keys->img_key00)
		error_exit2(g, "Failed: key00 image");
	g->textures->keys->img_key01 = load_textures(g, "src_textures/keys/key01.png");
	if (!g->textures->keys->img_key01)
		error_exit2(g, "Failed: key01 image");
	g->textures->keys->img_key02 = load_textures(g, "src_textures/keys/key02.png");
	if (!g->textures->keys->img_key02)
		error_exit2(g, "Failed: key02 image");
	g->textures->keys->img_key03 = load_textures(g, "src_textures/keys/key03.png");
	if (!g->textures->keys->img_key03)
		error_exit2(g, "Failed: key03 image");
	g->textures->keys->img_key04 = load_textures(g, "src_textures/keys/key04.png");
	if (!g->textures->keys->img_key04)
		error_exit2(g, "Failed: key04 image");
	g->textures->keys->img_key05 = load_textures(g, "src_textures/keys/key05.png");
	if (!g->textures->keys->img_key05)
		error_exit2(g, "Failed: key05 image");
	g->textures->keys->img_key06 = load_textures(g, "src_textures/keys/key06.png");
	if (!g->textures->keys->img_key06)
		error_exit2(g, "Failed: key06 image");
}


void	init_key_textures2(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
	g->textures->keys->img_key07 = load_textures(g, "src_textures/keys/key07.png");
	if (!g->textures->keys->img_key07)
		error_exit2(g, "Failed: key07 image");
	g->textures->keys->img_key08 = load_textures(g, "src_textures/keys/key08.png");
	if (!g->textures->keys->img_key08)
		error_exit2(g, "Failed: key08 image");
	g->textures->keys->img_key09 = load_textures(g, "src_textures/keys/key09.png");
	if (!g->textures->keys->img_key09)
		error_exit2(g, "Failed: key09 image");
	g->textures->keys->img_key10 = load_textures(g, "src_textures/keys/key10.png");
	if (!g->textures->keys->img_key10)
		error_exit2(g, "Failed: key10 image");
	g->textures->keys->img_key11 = load_textures(g, "src_textures/keys/key11.png");
	if (!g->textures->keys->img_key11)
		error_exit2(g, "Failed: key11 image");
	g->textures->keys->img_key12 = load_textures(g, "src_textures/keys/key12.png");;
	if (!g->textures->keys->img_key12)
		error_exit2(g, "Failed: key12 image");
	g->textures->keys->img_key13 = load_textures(g, "src_textures/keys/key13.png");
	if (!g->textures->keys->img_key13)
		error_exit2(g, "Failed: key13 image");
}

void	init_key_textures3(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		error_exit2(NULL, "Failure during uploading door/key textures");
	g->textures->keys->img_key14 = load_textures(g, "src_textures/keys/key14.png");
	if (!g->textures->keys->img_key14)
		error_exit2(g, "Failed: key14 image");
	g->textures->keys->img_key15 = load_textures(g, "src_textures/keys/key15.png");
	if (!g->textures->keys->img_key15)
		error_exit2(g, "Failed: key15 image");
	g->textures->keys->img_key16 = load_textures(g, "src_textures/keys/key16.png");
	if (!g->textures->keys->img_key16)
		error_exit2(g, "Failed: key16 image");
	g->textures->keys->img_key17 = load_textures(g, "src_textures/keys/key17.png");
	if (!g->textures->keys->img_key17)
		error_exit2(g, "Failed: key17 image");
	g->textures->keys->img_key18 = load_textures(g, "src_textures/keys/key18.png");
	if (!g->textures->keys->img_key18)
		error_exit2(g, "Failed: key18 image");
	g->textures->keys->img_key19 = load_textures(g, "src_textures/keys/key19.png");
	if (!g->textures->keys->img_key19)
		error_exit2(g, "Failed: key19 image");
	g->textures->keys->img_key20 = load_textures(g, "src_textures/keys/key20.png");
	if (!g->textures->keys->img_key20)
		error_exit2(g, "Failed: key20 image");	
}
