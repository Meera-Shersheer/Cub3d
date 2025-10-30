/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:32:11 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/30 11:01:49 by mshershe         ###   ########.fr       */
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
# include <math.h>
#include <sys/time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef FRAME_DURATION_MS
#define FRAME_DURATION_MS 40
#endif

#ifndef MIN_TILE_SIZE
#define MIN_TILE_SIZE 16 
#endif

#ifndef  SCALE_FACTOR
#define SCALE_FACTOR 0.9f  
#endif

#ifndef FOV
#define FOV (M_PI / 2.5f)  
#endif

# ifndef W_TILE
#  define W_TILE  96
# endif

# ifndef MINI_TILE
#  define MINI_TILE   (W_TILE / 4)
# endif


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

typedef struct s_corners
{
    int rows;
    int corners_x[2];
    int corners_y[2];
}   t_corners;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	uint32_t color;
}			t_color;


typedef struct s_sprite
{
	float		x;				// World position X
	float		y;				// World position Y
	float		dist;			// Distance from player (calculated each frame)
	mlx_image_t	*img;			// Sprite texture
	int			collected;		// 0 = visible, 1 = collected
	int			map_tile_x;		// Original map tile position
	int			map_tile_y;
	int screen_x;
	int screen_y;
	int			frame;			// Current frame index
	int			frame_count;	// Total number of frames
	//int			frame_delay;	// Frames to wait before switching
	//int			frame_timer;	// Counter for frame delay
	long		last_update_time;
	mlx_image_t	**frames;		// Array of frame images
}	t_sprite;

typedef struct s_sprite_list
{
	t_sprite	**sprites;		// Array of pointers to sprites
	int			count;			// Number of sprites
	int			capacity;		// Allocated space
}	t_sprite_list;

typedef struct s_ray_pos
{
	int		map_p;
	int		sign;
	float	pos;
	float	walk;
	float	delta_dist;
	int line_start;
	int	line_end;
}			t_ray_pos;

typedef struct s_item
{
    int x;
    int y;
    bool picked; // for key, false initially
} t_item;

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
	char	initial_look_dir;
	t_color	c_color;
	t_color	f_color;

    t_item key;
    t_item door;
}			t_map;

typedef struct s_player
{
    mlx_image_t *img;     // The player's sprite or rectangle
    float x;             // Player x position in the map (float for smooth movement)
    float y;             // Player y position
	float angle;
	float dir_x;         // Facing direction (unit vector x)
    float dir_y;         // Facing direction (unit vector y)
    float plane_x;       // Camera plane (for raycasting)
    float plane_y;
    float move_speed;    // Movement step per frame
    float rot_speed;     // Rotation speed
}   t_player;

typedef struct s_textures
{
	mlx_image_t *img_tex_no;
	mlx_image_t *img_tex_ea;
	mlx_image_t *img_tex_we;
	mlx_image_t *img_tex_so;
	struct s_key_textures	*keys;
	struct s_door_textures	*door;
}			t_textures;

typedef struct s_door_textures
{
	mlx_image_t *img_door_closed;
	mlx_image_t *img_door_opened;
	mlx_image_t *img_door_semi1;
	mlx_image_t *img_door_semi2;
}			t_door_textures;

typedef struct s_key_textures
{
	mlx_image_t *img_key00;
	mlx_image_t *img_key01;
	mlx_image_t *img_key02;
	mlx_image_t *img_key03;
	mlx_image_t *img_key04;
	mlx_image_t *img_key05;
	mlx_image_t *img_key06;
	mlx_image_t *img_key07;
	mlx_image_t *img_key08;
	mlx_image_t *img_key09;
	mlx_image_t *img_key10;
	mlx_image_t *img_key11;
	mlx_image_t *img_key12;
	mlx_image_t *img_key13;
	mlx_image_t *img_key14;
	mlx_image_t *img_key15;
	mlx_image_t *img_key16;
	mlx_image_t *img_key17;
	mlx_image_t *img_key18;
	mlx_image_t *img_key19;
	mlx_image_t *img_key20;
	mlx_image_t		*animation_frames[21];
}			t_key_textures;

typedef struct s_game
{
	mlx_t	*mlx;
	struct s_map	*map;
	struct s_player	*player;
	struct s_textures	*textures;
	t_sprite_list *sprites;
	mlx_image_t *map_2d;
	mlx_image_t *rays;
	mlx_image_t *scene_3d;
	int hit_side;
	mlx_texture_t *texture;
	mlx_image_t *img_tex;
	int total_keys;      // how many keys were spawned
	int collected_keys;  // how many player has picked
	int door_x;          // door coordinates
	int door_y;
	int door_open;       // 0 = closed, 1 = open
	int won; //0-> false   1-> true
	float *wall_distances;  // Track closest wall distance per column
	long game_time_start;
	long game_time_end;
	int w_tile;
	int mini_tile;
	double mouse_last_x;
}			t_game;

typedef struct s_ray
{
    float dir_x;
    float dir_y;
    int map_x;
    int map_y;
    float side_dist_x;
    float side_dist_y;
    float delta_dist_x;
    float delta_dist_y;
    int side;  // 0 = hit vertical wall (x-side), 1 = horizontal wall (y-side)
    float perp_wall_dist;
    // For drawing (2D & 3D)
    int hit;   // did we hit a wall?
    int wall_x; // used for texture mapping

}   t_ray;

typedef struct s_ray_hit3
{
    float ray_len;    // length returned by your find_stop_point (along ray)
    float perp_dist;  // corrected perpendicular distance (for projection)
    float hit_x;      // fractional hit position along the wall (0..1) - optional for textures
    int side;         // 0 = hit vertical gridline (x), 1 = horizontal gridline (y) - optional for shading
} t_ray_hit3;

typedef struct s_angle
{
    float cos_angle;
	float sin_angle;
	float	angle;
} t_angle;

typedef struct s_center
{
    int center_x;
	int center_y;
} t_center;

typedef struct s_wall_draw
{
    int     wall_height;
    int     draw_start;
    int     draw_end;
    int     tex_x;
    int     col;
}   t_wall_draw;

typedef struct s_dimention
{
    int     height;
    int     width;
}   t_dimention;

typedef struct s_ray_dic
{
	t_ray_pos	*x;
	t_ray_pos	*y;
}			t_ray_dic;

typedef enum e_wall_dir
{
    NORTH,  
    SOUTH, 
    EAST,  
    WEST,
	OTHER
}   t_wall_dir;

// check arg
int			check_arg(char *map_file);
int			ends_with_cub(const char *file_name);
int			parsing(int argc, char *argv[], t_game *game);

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
//void		check_map_outer_walls(t_map *map);
//void		check_map_inner_spaces(t_map *map);
int			skip_spaces(char *str, int i);
char		**split_lines_with_nl(char *content);
char		*trim_newline(char *str);
//padding
int			find_max_len(char **lines);
int			map_start(char *line);
int			map_end(char **lines, int i);
char		*pad_line(char *line, int max_length);
//flood_fill
//int			floodfill(t_map *map, char **grid, int pos_x, int pos_y);
void		floodfill(t_map *map, char **grid, int pos_x, int pos_y);
int			get_player_x_pos(char **grid);
int			get_player_y_pos(char **grid);
char		**cpy_matrix(char	**map);

//minimap
void draw_player(t_game *game);
void draw_2d_map(t_game *game);
void color_square_map2d (t_game *game, unsigned int color, mlx_image_t *img, int pixel_x, int pixel_y);
void pick_initial_angle (t_game *game);

void color_block (unsigned int color, mlx_image_t *img);

////
float abs_max (float num1, float num2);
void	dda(t_game *game);
void cast_rays(t_game *game, float angle);
int evaluate_delta_dist(t_ray_pos *x, t_ray_pos *y, t_angle *angle);
int evaluate_walk(t_ray_pos *i);
float	find_stop_point(t_game *game, t_ray_pos *x, t_ray_pos *y);
int check_acum_err(int err, int sd[4], t_ray_pos *x, t_ray_pos *y);
void	set_dir(t_angle *angle, t_ray_pos *x, t_ray_pos *y);


void try_move(t_game *g, float dx, float dy);
void move_right(t_game *g);
void move_left(t_game *g);
void move_backward(t_game *g);
void move_forward(t_game *g);

//3dscene

void draw_scene_and_rays(t_game *game);
void draw_single_col(t_game *game, float angle, int col);
void color_3d_scene(t_game *game, int col,t_angle *angle, t_ray_dic *rays);
int get_rgba(int r, int g, int b, int a);
void mouse_rotate(double xpos, double ypos, void *param);
uint32_t get_texture_color(t_game *game, float *tex_pos, float step, int tex_x, mlx_image_t *img_tex, int screen_y);
float eval_real_wall_dist(t_game *game, t_angle *angle, t_ray_pos *x, t_ray_pos *y);
void color_3d_floor_cielling(t_game *game, int col, int draw_start,  int draw_end);

//3dscene
int eval_wall_height(t_game *game,t_angle *angle, t_ray_dic *rays, int col);
int eval_tex_x(t_game *game, t_angle *angle, t_ray_dic *rays, mlx_image_t *img_tex);
float eval_real_wall_dist(t_game *game, t_angle *angle, t_ray_pos *x, t_ray_pos *y);

int init_textures(t_game *game);
mlx_image_t *get_wall_texture(t_game *game, t_ray_pos *x, t_ray_pos *y);
int get_wall_direction(t_game *game, t_ray_pos *x, t_ray_pos *y);

void place_keys_and_door(t_game *g);
void check_door(t_game *game);
void check_key_pickup(t_game *game);
void draw_door_symbol(t_game *game, mlx_image_t *img, int pixel_x, int pixel_y);
void draw_key_symbol(t_game *game, mlx_image_t *img, int pixel_x, int pixel_y);
void	check_keys_reachable(t_game *g);
int	reach_keys(t_map *map, char **grid, int x, int y);
int pseudo_random(int max);

//cleanup
void delete_textures(t_game *game);
void clean_sources(t_game *game);

int init_door_textures(t_game *g);
void	error_exit2(t_game *game, const char *msg);
int	init_key_textures(t_game *g);
void	init_key_textures1(t_game *g);
int	init_key_textures(t_game *g);
void	init_key_textures2(t_game *g);
void	init_key_textures3(t_game *g);



void render_all_sprites(t_game *game);
uint32_t get_sprite_texture(t_sprite *sprite, float u, float v);
void draw_sprite(t_game *game, t_sprite *sprite);
int get_sprite_height(t_game *game, t_sprite *sprite);
void update_sprite_distances(t_game *game);
void add_key_sprite(t_game *game, int map_x, int map_y);
void init_sprites(t_game *game);
void check_key_sprite_pickup(t_game *g, int tile_x, int tile_y);



////////////
void update_all_sprites_animation(t_game *game);
void update_sprite_animation(t_sprite *sprite);
void init_key_animation_frames(t_game *g);
mlx_image_t *load_textures(t_game *game, char *tex_path);

void sort_sprites(t_game *game);

long get_time(void);
void adjust_tile_size_to_screen(t_game *game, int map_width, int map_height);

#endif
