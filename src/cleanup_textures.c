/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 10:49:17 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/03 00:58:38 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
}

static void	delete_key_textures(t_game *g)
{
	int		i;
	void	**keys;

	if (!g || !g->textures || !g->textures->keys)
		return ;
	keys = (void **)&g->textures->keys->img_key00;
	i = 0;
	while (i <= 20)
	{
		if (keys[i])
			mlx_delete_image(g->mlx, keys[i]);
		i++;
	}
}

void	delete_textures(t_game *g)
{
	if (!g)
		return ;
	delete_wall_textures(g);
	delete_door_textures(g);
	delete_key_textures(g);
	if (g->textures)
		free(g->textures);
}
