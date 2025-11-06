/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 23:21:14 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/06 23:23:36 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	ft_strlen_number(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i] == '0')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		i++;
		len++;
	}
	return (len);
}

static int	validate_and_move_ptr(char **ptr, char *start,
	int value, int is_last)
{
	if (value < 0 || value > 255 || ft_strlen_number(start) > 3)
		return (0);
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
	if (is_last)
	{
		if (**ptr == ',' || **ptr != '\0')
			return (0);
	}
	else if (**ptr == ',')
		(*ptr)++;
	else
		return (0);
	return (1);
}

static int	handle_sign(char **ptr)
{
	int	sign_count;

	sign_count = 0;
	while (**ptr == '+' || **ptr == '-')
	{
		if (**ptr == '-')
			return (-1);
		sign_count++;
		if (sign_count > 1)
			return (-1);
		(*ptr)++;
	}
	return (0);
}

int	parse_component(char **ptr, int is_last)
{
	int		value;
	char	*start;

	if (!ptr || !*ptr)
		return (-1);
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
	if (handle_sign(ptr) < 0)
		return (-1);
	if (!ft_isdigit(**ptr))
		return (-1);
	start = *ptr;
	value = ft_atoi(start);
	while (**ptr && ft_isdigit(**ptr))
		(*ptr)++;
	if (!validate_and_move_ptr(ptr, start, value, is_last))
		return (-1);
	return (value);
}

int	parse_color_line(const char *line, t_color *color)
{
	char	*tmp;
	int		r;
	int		g;
	int		b;

	tmp = (char *)line;
	b = parse_component(&tmp, 0);
	r = parse_component(&tmp, 0);
	g = parse_component(&tmp, 1);
	if (r < 0 || g < 0 || b < 0)
		return (1);
	color->r = r;
	color->g = g;
	color->b = b;
	color->color = get_rgba(r, g, b, 0xFF);
	return (0);
}
