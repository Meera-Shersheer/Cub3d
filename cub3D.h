/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:32:11 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/09 16:52:55 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./Libft/ft_printf.h"
# include "./Libft/get_next_line_bonus.h"
# include "./Libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "MLX42/include/MLX42/MLX42.h"
# include <string.h>


typedef struct s_map
{
	int		screen_width;
	int		screen_height;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	*sprite_texture;
	char	*floor_color;
	char	*ceiling_color;
	char	**map_lines;
}			t_map;

//check arg
int 		check_arg(char *map_file);
int	ends_with_cub(const char *file_name);

//check map
int	read_map(char **av, char **content);
int	process_map(char *content, t_map *map);
int	check_map(char **av, t_map *map);

//init
void		init_map(t_map *map, size_t line_count);
void		print_map(t_map *map);

//utils
void		error_exit(const char *msg);

//read_file
void		copy_old_content(char *dest, char *content, size_t total);
char		*append_buffer(char *content, char *buffer, size_t total,
				ssize_t n);
char		*read_file(const char *path);

//parsing
void	classify_resolution(char *line, t_map *map);
void	classify_directional_textures(char *line, t_map *map);
void	classify_colors_and_sprite(char *line, t_map *map);
void	classify_map_lines(char **lines, t_map *map);
void		classify_lines(char **lines, t_map *map);

#endif