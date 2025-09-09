/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:41:05 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/09 17:33:17 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	read_map(char **av, char **content)
{
	*content = read_file(av[1]);
	if (!*content)
	{
		printf("Error\nFailed to read file\n");
		return (1);
	}
	return (0);
}

int	process_map(char *content, t_map *map)
{
	char	**lines;
	size_t	i;
	size_t	total_lines;

	lines = ft_split(content, '\n');
	if (!lines)
	{
		printf("Error\nFailed to split lines\n");
		return (1);
	}
	total_lines = 0;
	while (lines[total_lines])
		total_lines++;
	init_map(map, total_lines);
	classify_lines(lines, map);
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
	return (0);
}

int	check_map(char **av, t_map *map)
{
	char		*content;

	if (read_map(av, &content))
		return (1);
	if (process_map(content, map))
	{
		free(content);
		return (1);
	}
	free(content);
	return (0);
}
