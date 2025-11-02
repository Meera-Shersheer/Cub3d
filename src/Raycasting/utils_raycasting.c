/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:04:05 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/31 13:13:42 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	pseudo_random(int max)
{
	struct timeval	tv;

	if (max <= 0)
		return (0);
	gettimeofday(&tv, NULL);
	return ((tv.tv_usec ^ tv.tv_sec) % max);
}
