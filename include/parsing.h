/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:45:53 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/06 16:40:07 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# ifndef GREEN
#  define GREEN "\033[0;32m"
# endif

# ifndef MAGENTA
#  define MAGENTA "\033[0;35m"
# endif

# ifndef CYAN
#  define CYAN "\033[0;36m"
# endif

# ifndef RED
#  define RED "\033[0;31m"
# endif

# ifndef NC
#  define NC "\033[0m"
# endif

# ifndef BLUE
#define BLUE        "\033[0;34m"
# endif

# ifndef YELLOW
#define YELLOW	"\033[38;2;255;215;0m"
# endif

# ifndef  ORANGE 
#define ORANGE       "\033[38;5;208m"
# endif

typedef struct s_game	t_game;

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
	uint32_t			color;
}						t_color;
typedef struct s_item
{
	int					x;
	int					y;
	bool				picked;
}						t_item;
typedef struct s_map
{
	int					screen_width;
	int					screen_height;
	char				*north_texture;
	char				*south_texture;
	char				*west_texture;
	char				*east_texture;
	char				*floor_color;
	char				*ceiling_color;
	char				**map_lines;
	char				**flood_fill_map;
	char				**cpy_content;
	char				*msg;
	char				initial_look_dir;
	t_color				c_color;
	t_color				f_color;
	t_item				key;
	t_item				door;
}						t_map;

// check arg
int						check_arg(char *map_file);
int						ends_with_cub(const char *file_name);
int						parsing(int argc, char *argv[], t_game *game);
// check map
int						read_map(char **av, char **content);
int						process_map(char *content, t_map *map);
int						check_map(char **av, t_map *map);
void					check_playable_area(t_map *map);
// init
void					init_map(t_map *map, size_t line_count);
void					validate_map_values(t_map *map);
void					check_color(t_map *map);

// print
void					print_map(t_map *map);
void					print_floodfill_map(t_map *map);
void					print_start_header(void);
void					print_win_header(long time_ms);
// read_file
void					copy_old_content(char *dest, char *content,
							size_t total);
char					*append_buffer(char *content, char *buffer,
							size_t total, ssize_t n);
char					*read_file(const char *path);
// parsing
void					classify_resolution(char *line, t_map *map);
void					classify_map_lines(char **lines, t_map *map);
void					classify_config_lines(char **lines, t_map *map);
int						skip_spaces(char *str, int i);
// parsing2
void					classify_directional_textures(char *line, t_map *map);
void					classify_colors(char *line, t_map *map);

// validate map
int						check_map_order(char **lines);
void					check_player_position(t_map *map);
void					check_map_chars(t_map *map);
// check_texture
void					validate_textures(t_map *map);
// check_color
int						parse_color_line(const char *line, t_color *color);
int						get_rgba(int r, int g, int b, int a);

// split
char					**split_lines_with_nl(char *content);
char					*trim_newline(char *str);

// padding
int						find_max_len(char **lines);
int						map_start(char *line);
int						map_end(char **lines, int i);
char					*pad_line(char *line, int max_length);
// flood_fill

void					floodfill(t_map *map, char **grid, int pos_x,
							int pos_y);
int						get_player_x_pos(char **grid);
int						get_player_y_pos(char **grid);
char					**cpy_matrix(char **map);
// minimap
void					draw_player(t_game *game);
void					pick_initial_angle(t_game *game);
void					color_block(unsigned int color, mlx_image_t *img);
void					draw_map_tile(t_game *game, int x, int y);
int						get_tex_index(mlx_image_t *img_tex, int tex_x,
							int tex_y);

// minimap2
void					draw_2d_map(t_game *game);
void					color_square_map2d(t_game *game, unsigned int color,
							int pixel_x, int pixel_y);
float					abs_max(float num1, float num2);
#endif
