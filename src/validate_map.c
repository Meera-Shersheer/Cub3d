/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 06:15:40 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/16 05:47:37 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

void	check_map_chars(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map->map_lines[i])
	{
		j = 0;
		while (map->map_lines[i][j])
		{
			if (!is_valid_map_char(map->map_lines[i][j]))
				error_exit(map, "Invalid character in map");
			j++;
		}
		i++;
	}
}

void	check_player_position(t_map *map)
{
	int		count;
	size_t	i;
	size_t	j;

	count = 0;
	i = 0;
	while (map->map_lines[i])
	{
		j = 0;
		while (map->map_lines[i][j])
		{
			if (map->map_lines[i][j] == 'N' || map->map_lines[i][j] == 'S'
				|| map->map_lines[i][j] == 'E' || map->map_lines[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count > 1)
		error_exit(map, "Too many players, There must be exactly one player");
	else if (count < 1)
		error_exit(map, "There must be exactly one player");
}

int	check_map_order(char **lines)
{
	int		found_map;
	size_t	i;

	found_map = 0;
	i = 0;
	while (lines[i])
	{
		if (map_start(lines[i]))
			found_map = 1;
		else if (found_map && lines[i][0] != '\0')
			return (0);
		i++;
	}
	return (1);
}

/*
void	check_map_outer_walls(t_map *map)//remove later
{
	size_t	rows;
	size_t	i;
	size_t	j;

	rows = 0;
	while (map->map_lines[rows])
		rows++;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map->map_lines[i][j])
		{
			if ((map->map_lines[i][j] == '0' || map->map_lines[i][j] == 'N'
					|| map->map_lines[i][j] == 'S'
					|| map->map_lines[i][j] == 'E'
					|| map->map_lines[i][j] == 'W') && (i == 0 || i == rows - 1
					|| j == 0 || j == ft_strlen(map->map_lines[i]) - 1))
				error_exit(map, "Map is not fully closed by walls");
			j++;
		}
		i++;
	}
}

void	check_map_inner_spaces(t_map *map) // remove later
{
	size_t	rows;
	size_t	i;
	size_t	j;

	if (!map)
		error_exit(map, "NULL variable");
	rows = 0;
	while (map->map_lines[rows])
		rows++;
	i = 1;
	while (i < rows - 1)
	{
		j = 1;
		while (j < ft_strlen(map->map_lines[i]) - 1)
		{
			if ((map->map_lines[i][j] == '0' || map->map_lines[i][j] == 'N' || \
	map->map_lines[i][j] == 'S' || map->map_lines[i][j] == 'E' || \
	map->map_lines[i][j] == 'W') && (map->map_lines[i - 1][j] == ' ' || \
map->map_lines[i + 1][j] == ' ' || map->map_lines[i][j - 1] == ' ' || \
map->map_lines[i][j + 1] == ' '))
				error_exit(map, "Map is not closed by walls");
			j++;
		}
		i++;
	}
}*/