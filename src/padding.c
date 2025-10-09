/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:32:51 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/09 14:51:10 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*pad_line(char *line, int max_length)
{
	int		len;
	int		i;
	char	*padded;

	len = ft_strlen(line);
	padded = malloc(max_length + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < max_length)
	{
		padded[i] = ' ';
		i++;
	}
	padded[i] = '\0';
	return (padded);
}

int	find_max_len(char **lines)
{
	size_t	max;
	int		i;
	int		j;

	i = 0;
	max = 0;
	while (lines[i])
	{
		j = skip_spaces(lines[i], 0);
		if ((lines[i][j] == '0' || lines[i][j] == '1') && \
		ft_strlen(lines[i]) > max)
			max = ft_strlen(lines[i]);
		i++;
	}
	return (max);
}

int	map_start(char *line)
{
	int	j;

	j = skip_spaces(line, 0);
	if (line[j] == '0' || line[j] == '1')
		return (1);
	else
		return (0);
}

int	map_end(char **lines, int i)
{
	int	j;

	j = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0')
			j++;
		if (lines[i][0] != '\0' && j == 0)
			return (0);
		if (lines[i][0] != '\0' && j != 0)
			return (1);
		i++;
	}
	return (0);
}
