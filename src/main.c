/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/09 23:27:25 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
	{
		printf("Error\nIncorrect number of arguments\n");
		return (1);
	}
	if (check_arg(argv[1]))
		return (1);
	if (check_map(argv, &map))
		return (1);
	free_map(&map);
}
