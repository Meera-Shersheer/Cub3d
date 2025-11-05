/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:19:35 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/03 19:58:07 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"	

void	error_exit2(t_game *game, const char *msg)
{
	printf(RED "Error\n%s\n" NC, msg);
	clean_sources(game);
	exit(1);
}

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
	check_map_chars(map);
	check_player_position(map);
}

int	find_max(int num1, int num2)
{
	if (num1 > num2)
		return (num1);
	else
		return (num2);
}
