/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:04:52 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/23 18:18:15 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_free(char **matrix)
{
	size_t	row;

	row = 0;
	if (!matrix)
		return ;
	if (!(*matrix))
		return (free(matrix));
	while (row < ft_strlen_d(matrix))
	{
		free(matrix[row]);
		row++;
	}
	free(matrix);
}

void	free_textures(t_map *map)
{
	if (map->north_texture)
	{
		free(map->north_texture);
		map->north_texture = NULL;
	}
	if (map->south_texture)
	{
		free(map->south_texture);
		map->south_texture = NULL;
	}
	if (map->west_texture)
	{
		free(map->west_texture);
		map->west_texture = NULL;
	}
	if (map->east_texture)
	{
		free(map->east_texture);
		map->east_texture = NULL;
	}
}

static void	free_colors_and_maps(t_map *map)
{
	if (map->ceiling_color)
	{
		free(map->ceiling_color);
		map->ceiling_color = NULL;
	}
	if (map->floor_color)
	{
		free(map->floor_color);
		map->floor_color = NULL;
	}
	ft_free(map->map_lines);
	ft_free(map->cpy_content);
	ft_free(map->flood_fill_map);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_textures(map);
	free_colors_and_maps(map);
	if (map->msg)
		free(map->msg);
	if (map)
		free(map);
}

void clean_sources(t_game *game)
{
	if (game->player)
	{
    	if (game->player->img)
   			mlx_delete_image(game->mlx, game->player->img);
    	free(game->player);
    	game->player = NULL;
	}
    if (game->map_2d)
   		mlx_delete_image(game->mlx, game->map_2d);
	if (game->img_tex)
		mlx_delete_image(game->mlx, game->img_tex);
	if (game->rays)
		mlx_delete_image(game->mlx, game->rays);
	if (game->scene_3d)
		mlx_delete_image(game->mlx, game->scene_3d);
	free_map(game->map);
	delete_textures(game);
}

void delete_textures(t_game *game)
{
	if (!game)
		exit(1);//edit
	if (game->textures->img_tex_no)
	    mlx_delete_image(game->mlx, game->textures->img_tex_no);
	if (game->textures->tex_no)
	    mlx_delete_texture(game->textures->tex_no);	
	if (game->textures->img_tex_we)
	    mlx_delete_image(game->mlx, game->textures->img_tex_we);
	if (game->textures->tex_we)
	    mlx_delete_texture(game->textures->tex_we);
	if (game->textures->img_tex_ea)
	    mlx_delete_image(game->mlx, game->textures->img_tex_ea);
	if (game->textures->tex_ea)
	    mlx_delete_texture(game->textures->tex_ea);	
	if (game->textures->img_tex_so)
	    mlx_delete_image(game->mlx, game->textures->img_tex_so);
	if (game->textures->tex_so)
	    mlx_delete_texture(game->textures->tex_so);	
	if (game->textures->tex_door)
	    mlx_delete_texture(game->textures->tex_door);
	if (game->textures->img_tex_door)
	    mlx_delete_image(game->mlx, game->textures->img_tex_door);
	if(game->textures)
		free(game->textures);
}