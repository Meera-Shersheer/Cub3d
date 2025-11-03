/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:37:29 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/03 21:32:13 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

typedef struct s_sprite
{
	float		x;
	float		y;
	float		dist;
	mlx_image_t	*img;
	int			collected;
	int			map_tile_x;
	int			map_tile_y;
	int			screen_x;
	int			screen_y;
	int			frame;
	int			frame_count;
	long		last_update_time;
	mlx_image_t	**frames;
	int			width;
	int			height;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	int			cur_x;
	int			cur_y;
}				t_sprite;

typedef struct s_ray_pos
{
	int			map_p;
	int			sign;
	float		pos;
	float		walk;
	float		delta_dist;
	int			line_start;
	int			line_end;
}				t_ray_pos;

typedef struct s_ray_dic
{
	t_ray_pos	*x;
	t_ray_pos	*y;
}				t_ray_dic;

typedef struct s_angle
{
	float		cos_angle;
	float		sin_angle;
	float		angle;
}				t_angle;

typedef enum e_wall_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	OTHER
}				t_wall_dir;
typedef struct s_tex_info
{
	float		*tex_pos;
	float		step;
	int			tex_x;
	int			screen_y;
	mlx_image_t	*img_tex;
}				t_tex_info;

typedef struct s_corners
{
	int			rows;
	int			corners_x[2];
	int			corners_y[2];
}				t_corners;
typedef struct s_sprite_list
{
	t_sprite	**sprites;
	int			count;
	int			capacity;
}				t_sprite_list;

typedef struct s_dimention
{
	int			height;
	int			width;
}				t_dimention;
typedef struct s_wall_draw
{
	int			wall_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			col;
}				t_wall_draw;

typedef struct s_wall_context
{
	t_game		*game;
	t_angle		*angle;
	t_ray_dic	*rays;
	int			col;
	t_wall_draw	wall;
	t_tex_info	tex;
}				t_wall_context;
typedef struct s_ray
{
	float		dir_x;
	float		dir_y;
	int			map_x;
	int			map_y;
	float		side_dist_x;
	float		side_dist_y;
	float		delta_dist_x;
	float		delta_dist_y;
	int			side;
	float		perp_wall_dist;
	int			hit;
	int			wall_x;

}				t_ray;

typedef struct s_ray_hit3
{
	float		ray_len;
	float		perp_dist;
	float		hit_x;
	int			side;
}				t_ray_hit3;
typedef struct s_center
{
	int			center_x;
	int			center_y;
}				t_center;
typedef struct s_key_textures
{
	mlx_image_t	*img_key00;
	mlx_image_t	*img_key01;
	mlx_image_t	*img_key02;
	mlx_image_t	*img_key03;
	mlx_image_t	*img_key04;
	mlx_image_t	*img_key05;
	mlx_image_t	*img_key06;
	mlx_image_t	*img_key07;
	mlx_image_t	*img_key08;
	mlx_image_t	*img_key09;
	mlx_image_t	*img_key10;
	mlx_image_t	*img_key11;
	mlx_image_t	*img_key12;
	mlx_image_t	*img_key13;
	mlx_image_t	*img_key14;
	mlx_image_t	*img_key15;
	mlx_image_t	*img_key16;
	mlx_image_t	*img_key17;
	mlx_image_t	*img_key18;
	mlx_image_t	*img_key19;
	mlx_image_t	*img_key20;
	mlx_image_t	*animation_frames[21];
}				t_key_textures;

// rays
void			dda(t_game *game);
void			draw_scene_and_rays(t_game *game);
// rays2
void			cast_rays(t_game *game, float angle);
int				check_acum_err(int err, int sd[4], t_ray_pos *x, t_ray_pos *y);
// rays3
int				evaluate_delta_dist(t_ray_pos *x, t_ray_pos *y, t_angle *angle);
int				evaluate_walk(t_ray_pos *i);
float			find_stop_point(t_game *game, t_ray_pos *x, t_ray_pos *y);
void			set_dir(t_angle *angle, t_ray_pos *x, t_ray_pos *y);
// move
void			move_right(t_game *g);
void			move_left(t_game *g);
void			move_backward(t_game *g);
void			move_forward(t_game *g);
void			handle_additional_keys(mlx_key_data_t keydata, void *param);
// init_images1

int				init_textures(t_game *game);
int				init_door_textures(t_game *g);
void			init_sprites_allocation(t_game *game);
void			init_sprites_map_scan(t_game *game);

int				init_key_textures(t_game *g);
// init_images2
void			init_key_textures_part1(t_game *g);
void			init_key_textures_part2(t_game *g);
void			init_key_textures_part3(t_game *g);
mlx_image_t		*load_textures(t_game *game, char *tex_path);
// init_images3
void			init_key_textures_part4(t_game *g);
void			init_key_textures_part5(t_game *g);
void			init_key_textures_part6(t_game *g);
// door_key_reach
int				reach_keys(t_map *map, char **grid, int x, int y);
int				keys_reachable(t_game *g, char **map);
int				door_reachable(t_game *g, char **map);
int				reach_keys(t_map *map, char **grid, int x, int y);
int				reach_door(char **grid, int x, int y);
// adjust_window_size
void			adjust_tile_size_to_screen(t_game *game, int map_width,
					int map_height);
// animation
void			update_all_sprites_animation(t_game *game);
void			update_sprite_animation(t_sprite *sprite);
void			init_key_animation_frames(t_game *g);
void			render_all_sprites(t_game *game);
void			add_key_sprite(t_game *game, int map_x, int map_y);
// utils_raycasting
int				pseudo_random(int max);

// move2
void			move(void *param);
// init_game
void			init_game(int argc, char *argv[], t_game *game);
// utils_sprites
int				is_sprite_drawable(t_game *game, t_sprite *sprite);
void			sort_sprites(t_game *game);
long			get_time(void);
int				get_sprite_height(t_game *game, t_sprite *sprite);
// draw_sprites
void			draw_sprite(t_game *game, t_sprite *sprite);
// symbol
void			draw_door_symbol(t_game *game, mlx_image_t *img, int pixel_x,
					int pixel_y);
void			draw_key_symbol(t_game *game, mlx_image_t *img, int pixel_x,
					int pixel_y);
void			check_keys_reachable(t_game *g);
// sprites_texutres
uint32_t		get_sprite_texture(t_sprite *sprite, float u, float v);

// update_prites.c
void			update_sprite_distances(t_game *game);
// wall_texutres
mlx_image_t		*get_wall_texture(t_game *game, t_ray_pos *x, t_ray_pos *y);

// door_key
void			place_keys_and_door(t_game *g);
// door_key2
void			check_door(t_game *game);
void			check_key_pickup(t_game *game);
void			check_key_sprite_pickup(t_game *g, int tile_x, int tile_y);
// trymove
void			try_move(t_game *g, float dx, float dy);

// ray_casting
void			draw_single_col(t_game *game, float angle, int col);
int				eval_wall_height(t_game *game, t_angle *angle, t_ray_dic *rays,
					int col);
int				eval_tex_x(t_game *game, t_angle *angle, t_ray_dic *rays,
					mlx_image_t *img_tex);

// scene_3d
void			color_3d_scene(t_game *game, int col, t_angle *angle,
					t_ray_dic *rays);
int				get_wall_direction(t_game *game, t_ray_pos *x, t_ray_pos *y);
// scene_3d4
uint32_t		get_texture_color(t_game *game, t_tex_info *tex);
float			eval_real_wall_dist(t_game *game, t_angle *angle, t_ray_pos *x,
					t_ray_pos *y);
void			color_3d_floor_cielling(t_game *game, int col, int draw_start,
					int draw_end);
float			eval_real_wall_dist(t_game *game, t_angle *angle, t_ray_pos *x,
					t_ray_pos *y);

// scene3d3
int				get_wall_direction(t_game *game, t_ray_pos *x, t_ray_pos *y);
int				is_door_transparent(t_game *game, mlx_image_t *img_tex,
					uint8_t alpha);

#endif
