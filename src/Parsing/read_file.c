/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 20:31:53 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/09 19:02:29 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
		printf(RED "Error\nmalloc: %s\n" NC, strerror(errno));
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
		printf(RED "Error\n%s\n" NC, strerror(errno));
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
