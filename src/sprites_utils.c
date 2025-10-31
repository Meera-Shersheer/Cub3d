/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 22:56:31 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/31 22:59:31 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	swap_sprites(t_sprite **a, t_sprite **b)
{
	t_sprite	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	get_sprite_height(t_game *game, t_sprite *sprite)
{
	int	sprite_height;

	if (sprite->dist < 0.1f)
		sprite->dist = 0.1f;
	sprite_height = (int)(game->scene_3d->height / sprite->dist);
	return (sprite_height);
}
