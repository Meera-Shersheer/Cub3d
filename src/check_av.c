/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_av.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:41:05 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/08 19:48:20 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ends_with_cub(const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 4)
		return (0);
	if (name[len - 4] == '.' && name[len - 3] == 'c' && name[len - 2] == 'u'
		&& name[len - 1] == 'b')
		return (1);
	return (0);
}

void	copy_old_content(char *dest, char *content, size_t total)
{
	size_t	i;

	i = 0;
	while (i < total)
	{
		dest[i] = content[i];
		i++;
	}
}

char	*append_buffer(char *content, char *buffer, size_t total, ssize_t n)
{
	char	*new_content;
	size_t	j;

	new_content = malloc(total + n + 1);
	if (!new_content)
	{
		perror("malloc");
		free(content);
		exit(1);
	}
	copy_old_content(new_content, content, total);
	j = 0;
	while (j < (size_t)n)
	{
		new_content[total + j] = buffer[j];
		j++;
	}
	new_content[total + n] = '\0';
	free(content);
	return (new_content);
}

char	*read_file(const char *path)
{
	int		fd;
	char	buffer[1024];
	char	*content;
	size_t	total;
	ssize_t	n;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	content = NULL;
	total = 0;
	n = read(fd, buffer, sizeof(buffer));
	while (n > 0)
	{
		content = append_buffer(content, buffer, total, n);
		total += (size_t)n;
		n = read(fd, buffer, sizeof(buffer));
	}
	close(fd);
	return (content);
}
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
	char *content;
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
