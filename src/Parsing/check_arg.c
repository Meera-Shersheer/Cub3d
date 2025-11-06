/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:36:41 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/06 17:13:41 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	parsing(int argc, char *argv[], t_game *game)
{
	if (argc != 2)
	{
		printf(RED "Error\nIncorrect number of arguments\n" NC);
		return (1);
	}
	if (check_arg(argv[1]))
		return (1);
	if (check_map(argv, game))
		return (1);
	//adjust_tile_size_to_screen(game, game->map->screen_width,
	//	game->map->screen_height);
	return (0);
}

int	check_arg(char *map_file)
{
	if (!map_file)
	{
		printf(RED "Error\nNo map file\n" NC);
		return (1);
	}
	if (!ends_with_cub(map_file))
	{
		printf(RED "Error\nInvalid file extension: must end with .cub\n" NC);
		return (1);
	}
	return (0);
}

int	ends_with_cub(const char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 4)
		return (0);
	if (ft_strncmp(&(file_name[ft_strlen(file_name) - 4]), ".cub", 4) == 0)
		return (1);
	return (0);
}
