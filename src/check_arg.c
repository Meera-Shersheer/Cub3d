/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:36:41 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/09 16:43:36 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int check_arg(char *map_file)
{
	if (!map_file)
	{
		printf("Error\nNo map file\n");
		return (1);
	}
	if (!ends_with_cub(map_file))
	{
		printf("Error\nInvalid file extension: must end with .cub\n");
		return (1);
	}
	return (0);
}

int	ends_with_cub(const char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (len < 4)
		return (0);
	if (ft_strncmp(&(file_name[ft_strlen(file_name)- 4]), ".cub", 4) == 0)
		return (1);
	return (0);
}