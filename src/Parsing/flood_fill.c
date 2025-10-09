/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 01:06:38 by mshershe          #+#    #+#             */
/*   Updated: 2025/10/09 19:02:13 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"
/*
int	floodfill(t_map *map, char **grid, int pos_x, int pos_y)
{
	int	count;

	if (pos_x < 0 || pos_y < 0 || pos_x >= (int)ft_strlen_d(grid))
		error_exit(map, "Map is not fully closed");
	if (pos_y >= (int)ft_strlen(grid[pos_x]))
		error_exit(map, "Map is not fully closed");
	if (grid[pos_x][pos_y] == '1' || grid[pos_x][pos_y] == 'D')
		return (0);
	if (grid[pos_x][pos_y] == ' ')
		error_exit(map, "Map is not closed (Can reach a space)");
	grid[pos_x][pos_y] = 'D';
	count = 1;
	count += floodfill(map, grid, pos_x - 1, pos_y);
	count += floodfill(map, grid, pos_x + 1, pos_y);
	count += floodfill(map, grid, pos_x, pos_y - 1);
	count += floodfill(map, grid, pos_x, pos_y + 1);
	count += floodfill(map, grid, pos_x - 1, pos_y - 1);
	count += floodfill(map, grid, pos_x - 1, pos_y + 1);
	count += floodfill(map, grid, pos_x + 1, pos_y - 1);
	count += floodfill(map, grid, pos_x + 1, pos_y + 1);
	return (count);
}*/
void	floodfill(t_map *map, char **grid, int pos_x, int pos_y)
{
	if (pos_x < 0 || pos_y < 0 || pos_y >= (int)ft_strlen_d(grid))
		error_exit(map, "Map is not fully closed");
	if (pos_x >= (int)ft_strlen(grid[pos_y]))
		error_exit(map, "Map is not fully closed");
	if (grid[pos_y][pos_x] == '1' || grid[pos_y][pos_x] == 'D')
		return ;
	if (grid[pos_y][pos_x] == ' ')
		error_exit(map, "Map is not closed (Can reach a space)");
	grid[pos_y][pos_x] = 'D';
	floodfill(map, grid, pos_x - 1, pos_y);
	floodfill(map, grid, pos_x + 1, pos_y);
	floodfill(map, grid, pos_x, pos_y - 1);
	floodfill(map, grid, pos_x, pos_y + 1);
	floodfill(map, grid, pos_x - 1, pos_y - 1);
	floodfill(map, grid, pos_x - 1, pos_y + 1);
	floodfill(map, grid, pos_x + 1, pos_y - 1);
	floodfill(map, grid, pos_x + 1, pos_y + 1);
}

char	**cpy_matrix(char	**map)
{
	size_t	i;
	char	**map_cpy;

	i = 0;
	if (map == NULL || *map == NULL)
		return (NULL);
	map_cpy = malloc(sizeof(char *) * (ft_strlen_d(map) + 1));
	if (map_cpy == NULL)
		return (NULL);
	while (i < ft_strlen_d(map))
	{
		map_cpy[i] = ft_strdup((map[i]));
		i++;
	}
	map_cpy[i] = NULL;
	return (map_cpy);
}

int	get_player_y_pos(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S'
				|| grid[i][j] == 'E' || grid[i][j] == 'W')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int	get_player_x_pos(char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S'
				|| grid[i][j] == 'E' || grid[i][j] == 'W')
				return (j);
			j++;
		}
		i++;
	}
	return (-1);
}
