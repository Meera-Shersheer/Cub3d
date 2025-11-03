/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:22:05 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/09 19:02:38 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	*trim_newline(char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

size_t	count_lines(const char *content)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (!content)
		return (0);
	while (content[i])
	{
		if (content[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && content[i - 1] != '\n')
		count++;
	return (count);
}

static char	*extract_line(const char *content, size_t start, size_t *next_start)
{
	size_t	end;
	char	*line;

	end = start;
	while (content[end] && content[end] != '\n')
		end++;
	if (content[end] == '\n')
		end++;
	line = ft_substr(content, start, end - start);
	*next_start = end;
	return (line);
}

char	**split_lines_with_nl(char *content)
{
	size_t	i;
	size_t	start;
	size_t	lines_count;
	char	**lines;

	lines_count = count_lines(content);
	lines = malloc(sizeof(char *) * (lines_count + 1));
	if (!lines)
		return (NULL);
	i = 0;
	start = 0;
	while (i < lines_count)
	{
		lines[i] = extract_line(content, start, &start);
		i++;
	}
	lines[lines_count] = NULL;
	return (lines);
}
