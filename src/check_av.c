/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_av.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:41:05 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/08 20:31:35 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_and_read(int ac, char **av, char **content)
{
	if (ac != 2)
	{
		printf("Usage: %s <scene.cub>\n", av[0]);
		return (1);
	}
	if (!ends_with_cub(av[1]))
	{
		printf("Error! Invalid file extension: must end with .cub\n");
		return (1);
	}
	*content = read_file(av[1]);
	if (!*content)
	{
		printf("Error! Failed to read file\n");
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
		printf("Error! Failed to split lines\n");
		return (1);
	}
	total_lines = 0;
	while (lines[total_lines])
		total_lines++;
	init_map(map, total_lines);
	classify_lines(lines, map);
	print_map(map);
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
	return (0);
}

int	check_av(int ac, char **av, t_map *map)
{
	char		*content;

	if (validate_and_read(ac, av, &content))
		return (1);
	if (process_map(content, map))
	{
		free(content);
		return (1);
	}
	free(content);
	return (0);
}
