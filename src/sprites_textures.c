/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 01:03:11 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/03 01:03:23 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static int	get_sprite_tex_index(t_sprite *sprite, float u, float v)
{
	int	tex_x;
	int	tex_y;

	tex_x = (int)(u * sprite->img->width);
	tex_y = (int)(v * sprite->img->height);
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= (int)sprite->img->width)
		tex_x = sprite->img->width - 1;
	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= (int)sprite->img->height)
		tex_y = sprite->img->height - 1;
	return ((tex_y * sprite->img->width + tex_x) * 4);
}

uint32_t	get_sprite_texture(t_sprite *sprite, float u, float v)
{
	int		index;
	uint8_t	*p;
	uint8_t	rgba[4];
	int		i;

	i = 0;
	if (!sprite || !sprite->img || !sprite->img->pixels
		|| sprite->img->width == 0 || sprite->img->height == 0)
		return (0);
	index = get_sprite_tex_index(sprite, u, v);
	if (index + 3 >= (int)(sprite->img->width * sprite->img->height * 4))
		return (0);
	p = sprite->img->pixels;
	while (i < 4)
	{
		rgba[i] = p[index + i];
		i++;
	}
	return ((rgba[3] << 24) | (rgba[2] << 16) | (rgba[1] << 8) | rgba[0]);
}
