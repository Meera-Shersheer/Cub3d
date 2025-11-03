/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:32:11 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/03 12:43:16 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include ".././Libft/ft_printf.h"
# include ".././Libft/get_next_line_bonus.h"
# include ".././Libft/libft.h"
# include "../mlx42/include/MLX42/MLX42.h"
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
#include "parsing.h"
#include "raycasting.h"

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

typedef struct s_color t_color;

typedef struct s_sprite_list
{
	t_sprite	**sprites;		// Array of pointers to sprites
	int			count;			// Number of sprites
	int			capacity;		// Allocated space
}	t_sprite_list;



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
typedef struct s_tex_info
{
    float *tex_pos; 
    float step;
    int tex_x;
    int screen_y;
    mlx_image_t *img_tex;
} t_tex_info;

typedef struct s_wall_context
{
    t_game      *game;
    t_angle     *angle;
    t_ray_dic   *rays;
    int         col;
    t_wall_draw wall;
    t_tex_info  tex;
} t_wall_context;









// utils
void		error_exit(t_map *map, const char *msg);
size_t		ft_strlen_d(char **s);
void		check_map_values(t_map *map);
void		error_exit(t_map *map, const char *msg);
int find_max(int num1, int num2);
//cleanup
void		free_map(t_map *map);
void		ft_free(char **matrix);
void		free_map(t_map *map);
void clean_sources(t_game *game);
//input_handlers
void mouse_rotate(double xpos, double ypos, void *param);

void hide_map2d(mlx_key_data_t keydata, void *param);





//trymove
void try_move(t_game *g, float dx, float dy);

//3dscene

//ray_casting
void draw_single_col(t_game *game, float angle, int col);
int eval_wall_height(t_game *game,t_angle *angle, t_ray_dic *rays, int col);
int eval_tex_x(t_game *game, t_angle *angle, t_ray_dic *rays, mlx_image_t *img_tex);

//scene_3d
void color_3d_scene(t_game *game, int col,t_angle *angle, t_ray_dic *rays);
int get_wall_direction(t_game *game, t_ray_pos *x, t_ray_pos *y);
//scene_3d4
uint32_t get_texture_color(t_game *game, t_tex_info *tex);
float eval_real_wall_dist(t_game *game, t_angle *angle, t_ray_pos *x, t_ray_pos *y);
void color_3d_floor_cielling(t_game *game, int col, int draw_start,  int draw_end);
float eval_real_wall_dist(t_game *game, t_angle *angle, t_ray_pos *x, t_ray_pos *y);


//scene3d3
int get_wall_direction(t_game *game, t_ray_pos *x, t_ray_pos *y);
int	is_door_transparent(t_game *game, mlx_image_t *img_tex,
	uint8_t alpha);


//wall_texutres
mlx_image_t *get_wall_texture(t_game *game, t_ray_pos *x, t_ray_pos *y);

//door_key
void place_keys_and_door(t_game *g);
//door_key2
void check_door(t_game *game);
void check_key_pickup(t_game *game);

void check_key_sprite_pickup(t_game *g, int tile_x, int tile_y);




//cleanup




void	error_exit2(t_game *game, const char *msg);







//cleanup_texutre
void	delete_textures(t_game *g);


//sprites_texutres
uint32_t	get_sprite_texture(t_sprite *sprite, float u, float v);

//update_prites.c
void	update_sprite_distances(t_game *game);

#endif