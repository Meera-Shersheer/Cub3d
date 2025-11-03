#ifndef RAYCASTING_H
# define RAYCASTING_H
typedef struct s_sprite
{
	float x;          // World position X
	float y;          // World position Y
	float dist;       // Distance from player (calculated each frame)
	mlx_image_t *img; // Sprite texture
	int collected;    // 0 = visible, 1 = collected
	int map_tile_x;   // Original map tile position
	int		map_tile_y;
	int		screen_x;
	int		screen_y;
	int frame;       // Current frame index
	int frame_count; // Total number of frames
	// int			frame_delay;	// Frames to wait before switching
	// int			frame_timer;	// Counter for frame delay
	long	last_update_time;
	mlx_image_t **frames; // Array of frame images
	int		width;
	int		height;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		cur_x;
	int		cur_y;
}			t_sprite;

typedef struct s_ray_pos
{
	int		map_p;
	int		sign;
	float	pos;
	float	walk;
	float	delta_dist;
	int		line_start;
	int		line_end;
}			t_ray_pos;

typedef struct s_angle
{
	float	cos_angle;
	float	sin_angle;
	float	angle;
}			t_angle;

// rays
void		dda(t_game *game);
void		draw_scene_and_rays(t_game *game);
// rays2
void		cast_rays(t_game *game, float angle);
int			check_acum_err(int err, int sd[4], t_ray_pos *x, t_ray_pos *y);
// rays3
int			evaluate_delta_dist(t_ray_pos *x, t_ray_pos *y, t_angle *angle);
int			evaluate_walk(t_ray_pos *i);
float		find_stop_point(t_game *game, t_ray_pos *x, t_ray_pos *y);
void		set_dir(t_angle *angle, t_ray_pos *x, t_ray_pos *y);
// move
void		move_right(t_game *g);
void		move_left(t_game *g);
void		move_backward(t_game *g);
void		move_forward(t_game *g);

// init_images1

int			init_textures(t_game *game);
int			init_door_textures(t_game *g);
void		init_sprites_allocation(t_game *game);
void		init_sprites_map_scan(t_game *game);

int			init_key_textures(t_game *g);
// init_images2
void		init_key_textures_part1(t_game *g);
void		init_key_textures_part2(t_game *g);
void		init_key_textures_part3(t_game *g);
mlx_image_t	*load_textures(t_game *game, char *tex_path);
// init_images3
void		init_key_textures_part4(t_game *g);
void		init_key_textures_part5(t_game *g);
void		init_key_textures_part6(t_game *g);
// door_key_reach
int			reach_keys(t_map *map, char **grid, int x, int y);
int			keys_reachable(t_game *g, char **map);
int			door_reachable(t_game *g, char **map);
int			reach_keys(t_map *map, char **grid, int x, int y);
int			reach_door(char **grid, int x, int y);
// adjust_window_size
void		adjust_tile_size_to_screen(t_game *game, int map_width,
				int map_height);
// animation
void		update_all_sprites_animation(t_game *game);
void		update_sprite_animation(t_sprite *sprite);
void		init_key_animation_frames(t_game *g);
void		render_all_sprites(t_game *game);
void		add_key_sprite(t_game *game, int map_x, int map_y);
// utils_raycasting
int			pseudo_random(int max);

// move2
void		move(void *param);
// init_game
void		init_game(int argc, char *argv[], t_game *game);
// utils_sprites
int			is_sprite_drawable(t_game *game, t_sprite *sprite);
void		sort_sprites(t_game *game);
long		get_time(void);
int			get_sprite_height(t_game *game, t_sprite *sprite);
// draw_sprites
void		draw_sprite(t_game *game, t_sprite *sprite);
// symbol
void		draw_door_symbol(t_game *game, mlx_image_t *img, int pixel_x,
				int pixel_y);
void		draw_key_symbol(t_game *game, mlx_image_t *img, int pixel_x,
				int pixel_y);
void		check_keys_reachable(t_game *g);

#endif
