/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:36:41 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/08 21:35:17 by mshershe         ###   ########.fr       */
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
	printf("[%s]\n", map_file);
	//first tke the link of the map file
	//reprint it on terminal as a first check
	//write function checks
	//check extension
	//check if file exist 
	// check if the file has the right permissions
	// the file is working --> great 
	//now for parsing
	// open map and read it using read 
	//and do the checks
	return (0);
	
}