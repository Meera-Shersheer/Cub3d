/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:32:11 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/03 21:18:20 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include ".././Libft/ft_printf.h"
# include ".././Libft/get_next_line_bonus.h"
# include ".././Libft/libft.h"
# include "../../MLX42/include/MLX42/MLX42.h"
# include "parsing.h"
# include "raycasting.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef FRAME_DURATION_MS
#  define FRAME_DURATION_MS 30
# endif

# ifndef MIN_TILE_SIZE
#  define MIN_TILE_SIZE 16
# endif

# ifndef SCALE_FACTOR
#  define SCALE_FACTOR 0.9f
# endif

# ifndef FOV
#  define FOV 1.25663706144f
# endif

# ifndef W_TILE
#  define W_TILE 64
# endif

# ifndef MINI_TILE
#  define MINI_TILE 16
# endif

typedef struct s_player
{
	mlx_image_t				*img;
	float					x;
	float					y;
	float					angle;
	float					dir_x;
	float					dir_y;
	float					plane_x;
	float					plane_y;
	float					move_speed;
	float					rot_speed;
}							t_player;

typedef struct s_textures
{
	mlx_image_t				*img_tex_no;
	mlx_image_t				*img_tex_ea;
	mlx_image_t				*img_tex_we;
	mlx_image_t				*img_tex_so;
	struct s_key_textures	*keys;
	struct s_door_textures	*door;
}							t_textures;

typedef struct s_door_textures
{
	mlx_image_t				*img_door_closed;
	mlx_image_t				*img_door_opened;
	mlx_image_t				*img_door_semi1;
	mlx_image_t				*img_door_semi2;
}							t_door_textures;

typedef struct s_game
{
	mlx_t					*mlx;
	struct s_map			*map;
	struct s_player			*player;
	struct s_textures		*textures;
	t_sprite_list			*sprites;
	mlx_image_t				*map_2d;
	mlx_image_t				*rays;
	mlx_image_t				*scene_3d;
	int						hit_side;
	mlx_texture_t			*texture;
	mlx_image_t				*img_tex;
	int						total_keys;
	int						collected_keys;
	int						door_x;
	int						door_y;
	int						door_open;
	int						won;
	float					*wall_distances;
	long					game_time_start;
	long					game_time_end;
	int						w_tile;
	int						mini_tile;
	double					mouse_last_x;
}							t_game;

// utils
void						error_exit(t_map *map, const char *msg);
size_t						ft_strlen_d(char **s);
void						check_map_values(t_map *map);
void						error_exit2(t_game *game, const char *msg);
int							find_max(int num1, int num2);
// cleanup
void						free_map(t_map *map);
void						ft_free(char **matrix);
void						free_map(t_map *map);
void						clean_sources(t_game *game);
void						ft_free_sprites(t_game *g);
// input_handlers
void						mouse_rotate(double xpos, double ypos, void *param);
void						hide_map2d(mlx_key_data_t keydata, void *param);
// cleanup_texutre
void						delete_textures(t_game *g);
#endif