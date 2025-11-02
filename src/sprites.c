/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:55:44 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/31 22:55:58 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	get_texture_index(t_sprite *sprite, float u, float v)
{
	int	tex_x;
	int	tex_y;

	if (!sprite || !sprite->img || !sprite->img->pixels)
		return (-1);
	if (sprite->img->width == 0 || sprite->img->height == 0)
		return (-1);
	tex_x = (int)(u * sprite->img->width);
	tex_y = (int)(v * sprite->img->height);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)sprite->img->width)
		tex_x = sprite->img->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)sprite->img->height)
		tex_y = sprite->img->height - 1;
	return ((tex_y * sprite->img->width + tex_x) * 4);
}

static uint32_t	extract_color(uint8_t *p, int tex_index)
{
	uint8_t	a;
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;

	a = p[tex_index];
	b = p[tex_index + 1];
	g = p[tex_index + 2];
	r = p[tex_index + 3];
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

uint32_t	get_sprite_texture(t_sprite *sprite, float u, float v)
{
	int		tex_index;
	int		max_index;
	uint8_t	*p;

	tex_index = get_texture_index(sprite, u, v);
	if (tex_index < 0)
		return (0);
	max_index = sprite->img->width * sprite->img->height * 4;
	if (tex_index + 3 >= max_index)
		return (0);
	p = sprite->img->pixels;
	return (extract_color(p, tex_index));
}

static void	sort_sprites_pass(t_game *g, int end)
{
	int	j;

	j = 0;
	while (j < end)
	{
		if (g->sprites->sprites[j] && g->sprites->sprites[j + 1])
		{
			if (g->sprites->sprites[j]->dist < g->sprites->sprites[j + 1]->dist)
				swap_sprites(&g->sprites->sprites[j], &g->sprites->sprites[j
					+ 1]);
		}
		j++;
	}
}

void	sort_sprites(t_game *g)
{
	int	i;

	if (!g || !g->sprites || g->sprites->count <= 1)
		return ;
	i = 0;
	while (i < g->sprites->count - 1)
	{
		sort_sprites_pass(g, g->sprites->count - i - 1);
		i++;
	}
}
