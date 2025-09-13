/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/13 15:09:58 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
	{
		printf(RED "Error\nIncorrect number of arguments\n" NC);
		return (1);
	}
	if (check_arg(argv[1]))
		return (1);
	if (check_map(argv, &map))
		return (1);
	free_map(&map);
}
