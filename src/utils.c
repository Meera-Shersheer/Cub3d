/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:19:35 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/14 00:33:33 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	error_exit(t_map *map, const char *msg)
{
	printf(RED "Error\n%s\n" NC, msg);
	free_map(map);
	exit(1);
}

size_t	ft_strlen_d(char **s)
{
	size_t	n;

	n = 0;
	if (s == NULL || *s == NULL)
		return (0);
	while (s[n] != NULL)
		n++;
	return (n);
}

void	check_map_values(t_map *map)
{
	check_map_outer_walls(map);
	check_map_inner_spaces(map);
	check_map_chars(map);
	check_player_position(map);
}
