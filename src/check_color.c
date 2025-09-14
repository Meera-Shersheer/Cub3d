/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:21:14 by aalmahas          #+#    #+#             */
/*   Updated: 2025/09/14 04:46:16 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	parse_component(char **ptr)
{
	int	value;

	if (!ptr || !*ptr)
		return (-1);
	while (**ptr == ' ')
		(*ptr)++;
	if (!ft_isdigit(**ptr))
		return (-1);
	value = ft_atoi(*ptr);
	while (**ptr && **ptr != ',')
		(*ptr)++;
	if (**ptr == ',')
		(*ptr)++;
	return (value);
}

int	parse_color_line(const char *line, t_color *color)
{
	char	*tmp;
	int		r;
	int		g;
	int		b;

	tmp = (char *)line;
	r = parse_component(&tmp);
	g = parse_component(&tmp);
	b = parse_component(&tmp);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	color->r = r;
	color->g = g;
	color->b = b;
	return (0);
}
