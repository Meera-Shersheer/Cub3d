/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 21:19:35 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/09 21:15:01 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	error_exit(t_map *map, const char *msg)
{
	free_map(map);
	printf("Error\n%s\n", msg);
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

void	ft_free(char **matrix)
{
	size_t	row;

	row = 0;
	if (!matrix)
		return ;
	if (!(*matrix))
		return (free(matrix));
	while (row < ft_strlen_d(matrix))
	{
		free (matrix[row]);
		row++;
	}
	free (matrix);
}

void    free_map(t_map *map)
{
    if (!map)
        return;
    if (map->north_texture)
    {
        free(map->north_texture);
        map->north_texture = NULL;
    }
    if (map->south_texture)
    {
        free(map->south_texture);
        map->south_texture = NULL;
    }
    if (map->west_texture)
    {
        free(map->west_texture);
        map->west_texture = NULL;
    }
    if (map->east_texture)
    {
        free(map->east_texture);
        map->east_texture = NULL;
    }
	 if (map->ceiling_color)
    {
        free(map->ceiling_color);
        map->ceiling_color = NULL;
    }
	 if (map->floor_color)
    {
        free(map->floor_color);
        map->floor_color = NULL;
    }
   ft_free(map->map_lines);
   ft_free(map->cpy_content);
}
