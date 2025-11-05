/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:49:17 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/03 20:06:57 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	delete_wall_textures(t_game *g)
{
	if (!g || !g->textures)
		return ;
	if (g->textures->img_tex_no)
		mlx_delete_image(g->mlx, g->textures->img_tex_no);
	if (g->textures->img_tex_ea)
		mlx_delete_image(g->mlx, g->textures->img_tex_ea);
	if (g->textures->img_tex_we)
		mlx_delete_image(g->mlx, g->textures->img_tex_we);
	if (g->textures->img_tex_so)
		mlx_delete_image(g->mlx, g->textures->img_tex_so);
}

static void	delete_door_textures(t_game *g)
{
	if (!g || !g->textures || !g->textures->door)
		return ;
	if (g->textures->door->img_door_closed)
		mlx_delete_image(g->mlx, g->textures->door->img_door_closed);
	if (g->textures->door->img_door_opened)
		mlx_delete_image(g->mlx, g->textures->door->img_door_opened);
	if (g->textures->door)
		free (g->textures->door);
}

static void	delete_key_textures1(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		return ;
	if (g->textures->keys->img_key00)
		mlx_delete_image(g->mlx, g->textures->keys->img_key00);
	if (g->textures->keys->img_key01)
		mlx_delete_image(g->mlx, g->textures->keys->img_key01);
	if (g->textures->keys->img_key02)
		mlx_delete_image(g->mlx, g->textures->keys->img_key02);
	if (g->textures->keys->img_key03)
		mlx_delete_image(g->mlx, g->textures->keys->img_key03);
	if (g->textures->keys->img_key04)
		mlx_delete_image(g->mlx, g->textures->keys->img_key04);
	if (g->textures->keys->img_key05)
		mlx_delete_image(g->mlx, g->textures->keys->img_key05);
	if (g->textures->keys->img_key06)
		mlx_delete_image(g->mlx, g->textures->keys->img_key06);
	if (g->textures->keys->img_key07)
		mlx_delete_image(g->mlx, g->textures->keys->img_key07);
	if (g->textures->keys->img_key08)
		mlx_delete_image(g->mlx, g->textures->keys->img_key08);
	if (g->textures->keys->img_key09)
		mlx_delete_image(g->mlx, g->textures->keys->img_key09);
	if (g->textures->keys->img_key10)
		mlx_delete_image(g->mlx, g->textures->keys->img_key10);
}

static void	delete_key_textures2(t_game *g)
{
	if (!g || !g->textures || !g->textures->keys)
		return ;
	if (g->textures->keys->img_key11)
		mlx_delete_image(g->mlx, g->textures->keys->img_key11);
	if (g->textures->keys->img_key12)
		mlx_delete_image(g->mlx, g->textures->keys->img_key12);
	if (g->textures->keys->img_key13)
		mlx_delete_image(g->mlx, g->textures->keys->img_key13);
	if (g->textures->keys->img_key14)
		mlx_delete_image(g->mlx, g->textures->keys->img_key14);
	if (g->textures->keys->img_key15)
		mlx_delete_image(g->mlx, g->textures->keys->img_key15);
	if (g->textures->keys->img_key16)
		mlx_delete_image(g->mlx, g->textures->keys->img_key16);
	if (g->textures->keys->img_key17)
		mlx_delete_image(g->mlx, g->textures->keys->img_key17);
	if (g->textures->keys->img_key18)
		mlx_delete_image(g->mlx, g->textures->keys->img_key18);
	if (g->textures->keys->img_key19)
		mlx_delete_image(g->mlx, g->textures->keys->img_key19);
	if (g->textures->keys->img_key20)
		mlx_delete_image(g->mlx, g->textures->keys->img_key20);
	if (g->textures->keys)
		free (g->textures->keys);
}

void	delete_textures(t_game *g)
{
	if (!g)
		return ;
	delete_wall_textures(g);
	delete_door_textures(g);
	delete_key_textures1(g);
	delete_key_textures2(g);
	if (g->textures)
		free(g->textures);
}
