/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:32:11 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/16 05:49:29 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./Libft/ft_printf.h"
# include "./Libft/get_next_line_bonus.h"
# include "./Libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef GREEN
#  define GREEN   "\033[0;32m"
# endif

# ifndef MAGENTA
#  define MAGENTA "\033[0;35m"
# endif

# ifndef CYAN
#  define CYAN    "\033[0;36m"
# endif

# ifndef RED
#  define RED     "\033[0;31m"
# endif

# ifndef NC
#  define NC      "\033[0m"
# endif

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_map
{
	int		screen_width;
	int		screen_height;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	*floor_color;
	char	*ceiling_color;
	char	**map_lines;
	char	**flood_fill_map;
	char	**cpy_content;
	char	*msg;
	t_color	c_color;
	t_color	f_color;
}			t_map;

// check arg
int			check_arg(char *map_file);
int			ends_with_cub(const char *file_name);

// check map
int			read_map(char **av, char **content);
int			process_map(char *content, t_map *map);
int			check_map(char **av, t_map *map);
void		check_playable_area( t_map *map);

// init
void		init_map(t_map *map, size_t line_count);

//print
void		print_map(t_map *map);
void		print_floodfill_map(t_map *map);

// utils
void		error_exit(t_map *map, const char *msg);
void		free_map(t_map *map);
void		ft_free(char **matrix);
size_t		ft_strlen_d(char **s);
// read_file
void		copy_old_content(char *dest, char *content, size_t total);
char		*append_buffer(char *content, char *buffer, size_t total,
				ssize_t n);
char		*read_file(const char *path);

// parsing
void		classify_resolution(char *line, t_map *map);
void		classify_directional_textures(char *line, t_map *map);
void		classify_colors(char *line, t_map *map);
void		classify_map_lines(char **lines, t_map *map);
void		classify_config_lines(char **lines, t_map *map);

//validate map
void		validate_map_values(t_map *map);
void		validate_textures(t_map *map);
int			parse_color_line(const char *line, t_color *color);
void		check_color(t_map *map);
int			check_map_order(char **lines);

void		free_map(t_map *map);

void		error_exit(t_map *map, const char *msg);
void		check_map_values(t_map *map);

void		check_player_position(t_map *map);
void		check_map_chars(t_map *map);
void		check_map_outer_walls(t_map *map);
void		check_map_inner_spaces(t_map *map);
int			skip_spaces(char *str, int i);
char		**split_lines_with_nl(char *content);
char		*trim_newline(char *str);
//padding
int			find_max_len(char **lines);
int			map_start(char *line);
int			map_end(char **lines, int i);
char		*pad_line(char *line, int max_length);
//flood_fill
void		floodfill(t_map *map, char **grid, int pos_x, int pos_y);
int			get_player_x_pos(char **grid);
int			get_player_y_pos(char **grid);
char		**cpy_matrix(char	**map);
#endif