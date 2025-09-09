/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:09:56 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/08 21:43:33 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf ("Error\nIncorrect number of arguments\n");
		return (1);
	}
	check_arg(argv[1]);
	
	//write function checks
	//check extension
	//check if file exist 
	// check if the file has the right permissions
	// the file is working --> great 
	//now for parsing
	// open map and read it using read 
	//and do the checks
	
}