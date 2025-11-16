/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/16 16:51:51 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
	/*To test leaks:  valgrind --leak-check=full  --show-leak-kinds=all
	--track-origins=yes --suppressions=mlx.supp
	--log-file=valgrind_output.txt ./cub3D map*/

int	main(int argc, char *argv[])
{
	t_game	game;
	int		i;

	init_game(argc, argv, &game);
	draw_2d_map(&game);
	draw_player(&game);
	draw_scene_and_rays(&game);
	game.game_time_start = get_time();
	if (game.wall_distances && game.scene_3d)
	{
		i = 0;
		while (i < (int)game.scene_3d->width)
			game.wall_distances[i++] = 10000.0f;
	}
	render_all_sprites(&game);
	mlx_key_hook(game.mlx, handle_additional_keys, &game);
	mlx_cursor_hook(game.mlx, mouse_rotate, &game);
	mlx_loop_hook(game.mlx, &move, &game);
	mlx_loop(game.mlx);
	clean_sources(&game);
	mlx_terminate(game.mlx);
	return (0);
}

void	ft_free_sprites2(t_game *g, int i)
{
	int	j;

	if (!g || !g->sprites)
		return ;
	j = g->sprites->count - 1;
	while (j >= 0)
	{
		if (g->sprites->sprites[i] && g->sprites->sprites[i]->frames[j])
			mlx_delete_image(g->mlx, g->sprites->sprites[i]->frames[j]);
		j--;
	}
}

void	ft_free_sprites(t_game *g)
{
	int	i;

	i = g->total_keys - 1;
	if (!g || !g->sprites)
		return ;
	if (g->sprites->sprites)
	{
		while (i >= 0)
		{
			ft_free_sprites2(g, i);
			if (g->sprites->sprites[i]->img)
				mlx_delete_image(g->mlx, g->sprites->sprites[i]->img);
			if (g->sprites->sprites[i])
				free (g->sprites->sprites[i]);
			i--;
		}
	}
	if (g->sprites->sprites)
		free (g->sprites->sprites);
	if (g->sprites)
		free (g->sprites);
}

void	error_exit3(t_game *game, const char *msg)
{
	if (msg)
		printf(RED "Error\n%s\n" NC, msg);
	if (game)
	{
		mlx_close_window(game->mlx);
		clean_sources(game);
		mlx_terminate(game->mlx);
	}
	exit(1);
}

void	error_exit_fd(t_map *map, const char *msg, int fd)
{
	if (fd >= 0)
		close (fd);
	if (msg)
		printf(RED "Error\n%s\n" NC, msg);
	free_map(map);
	exit(1);
}
