/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 23:46:54 by aalmahas          #+#    #+#             */
/*   Updated: 2025/11/03 13:03:56 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	swap_if_needed(t_sprite **a, t_sprite **b)
{
	t_sprite	*temp;

	if (*a && *b && (*a)->dist < (*b)->dist)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

void	sort_sprites(t_game *game)
{
	int	i;
	int	j;

	if (!game || !game->sprites || game->sprites->count <= 1)
		return ;
	i = 0;
	while (i < game->sprites->count - 1)
	{
		j = 0;
		while (j < game->sprites->count - i - 1)
		{
			swap_if_needed(&game->sprites->sprites[j], &game->sprites->sprites[j
				+ 1]);
			j++;
		}
		i++;
	}
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	get_sprite_height(t_game *game, t_sprite *sprite)
{
	int		sprite_height;

	if (sprite->dist < 0.1f)
		sprite->dist = 0.1f;
	sprite_height = (int)(game->scene_3d->height / sprite->dist);
	return (sprite_height);
}

int	is_sprite_drawable(t_game *game, t_sprite *sprite)
{
	if (!game || !sprite || !sprite->img || sprite->collected == 1)
		return (0);
	if (!game->wall_distances || !game->scene_3d || !game->scene_3d->pixels)
		return (0);
	if (sprite->screen_x < -500 || sprite->screen_x > (int)game->scene_3d->width
		+ 500)
		return (0);
	return (1);
}
