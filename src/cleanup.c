/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:04:52 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/25 00:29:56 by mshershe         ###   ########.fr       */
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
void delete_tex_img(mlx_t *mlx, mlx_texture_t *tex, mlx_image_t *img)
{
    if (img)
        mlx_delete_image(mlx, img);
    if (tex)
        mlx_delete_texture(tex);
}
void delete_textures(t_game *g)
{
	if (!g)
		exit(1);//edit
	delete_tex_img(g->mlx, g->textures->tex_no, g->textures->img_tex_no);
    delete_tex_img(g->mlx, g->textures->tex_ea, g->textures->img_tex_ea);
    delete_tex_img(g->mlx, g->textures->tex_we, g->textures->img_tex_we);
    delete_tex_img(g->mlx, g->textures->tex_so, g->textures->img_tex_so);
	if(g->textures)
		free(g->textures);
}
