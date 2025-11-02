/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:04:52 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/30 21:36:19 by mshershe         ###   ########.fr       */
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
	if (game->wall_distances)
	{
		free(game->wall_distances);
		game->wall_distances = NULL;
	}
	free_map(game->map);
	delete_textures(game);
}

void delete_textures(t_game *g)
{
	if (!g || !g->textures)
		exit(1);//edit
	if ( g->textures->img_tex_no)
        mlx_delete_image(g->mlx, g->textures->img_tex_no);
	if ( g->textures->img_tex_no)
        mlx_delete_image(g->mlx, g->textures->img_tex_ea);
	if ( g->textures->img_tex_no)
        mlx_delete_image(g->mlx, g->textures->img_tex_we);
	if ( g->textures->img_tex_no)
        mlx_delete_image(g->mlx, g->textures->img_tex_so);

	if ( g->textures->door->img_door_closed)
        mlx_delete_image(g->mlx, g->textures->door->img_door_closed);
	if ( g->textures->door->img_door_opened)
        mlx_delete_image(g->mlx, g->textures->door->img_door_opened);
		
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
		free(g->textures->keys);
	if(g->textures)
		free(g->textures);
}


void delete_sprites(t_game *g)
{
	if (!g)
		exit(1);//edit

    
}