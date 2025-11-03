/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:34:29 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/31 18:35:54 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	is_valid_texture_inputs(t_game *game, t_ray_pos *x, t_ray_pos *y)
{
	if (!game || !game->textures || !x || !y)
	{
		printf("ERROR: get_wall_texture null pointer!\n");
		return (0);
	}
	if (y->map_p < 0 || y->map_p >= (int)ft_strlen_d(game->map->map_lines)
		|| x->map_p < 0
		|| x->map_p >= (int)ft_strlen(game->map->map_lines[y->map_p]))
		return (0);
	return (1);
}

static mlx_image_t	*get_door_texture(t_game *game)
{
	if (!game->textures->door)
	{
		printf("ERROR: DOOR textures is NULL!\n");
		return (NULL);
	}
	if (game->door_open == 0)
		return (game->textures->door->img_door_closed);
	return (game->textures->door->img_door_opened);
}

static mlx_image_t	*get_direction_texture(t_game *game, int direction)
{
	if (direction == NORTH)
	{
		if (!game->textures->img_tex_no)
			printf("ERROR: NORTH texture is NULL!\n");
		return (game->textures->img_tex_no);
	}
	if (direction == SOUTH)
	{
		if (!game->textures->img_tex_so)
			printf("ERROR: SOUTH texture is NULL!\n");
		return (game->textures->img_tex_so);
	}
	if (direction == EAST)
	{
		if (!game->textures->img_tex_ea)
			printf("ERROR: EAST texture is NULL!\n");
		return (game->textures->img_tex_ea);
	}
	if (direction == WEST)
	{
		if (!game->textures->img_tex_we)
			printf("ERROR: WEST texture is NULL!\n");
		return (game->textures->img_tex_we);
	}
	return (NULL);
}

mlx_image_t	*get_wall_texture(t_game *game, t_ray_pos *x, t_ray_pos *y)
{
	int	direction;

	if (!is_valid_texture_inputs(game, x, y))
		return (NULL);
	if (game->map->map_lines[y->map_p][x->map_p] == 'D')
		return (get_door_texture(game));
	direction = get_wall_direction(game, x, y);
	return (get_direction_texture(game, direction));
}
