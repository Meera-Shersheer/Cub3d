/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:08:45 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/08 19:39:17 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

typedef struct s_map
{
    int     screen_width;
    int     screen_height;
    char    *north_texture;
    char    *south_texture;
    char    *west_texture;
    char    *east_texture;
    char    *sprite_texture;
    char    *floor_color;
    char    *ceiling_color;
    char    **map_lines;
}   t_map;

int	check_av(int ac, char **av, t_map *map);


void classify_lines(char **lines, t_map *map);
void	init_map(t_map *map, size_t line_count);
void	print_map(t_map *map);

#endif