#include "../cub3D.h"

static void compute_sprite_distance(t_game *game, t_sprite *sprite, float *raw_dist, float *angle_diff)
{
	float dx = sprite->x - (game->player->x + game->player->img->width / 2.0f);
	float dy = sprite->y - (game->player->y + game->player->img->height / 2.0f);

	*raw_dist = sqrtf(dx * dx + dy * dy);
	*angle_diff = atan2f(dy, dx) - game->player->angle;

	while (*angle_diff > M_PI)
		*angle_diff -= 2 * M_PI;
	while (*angle_diff < -M_PI)
		*angle_diff += 2 * M_PI;

	sprite->dist = *raw_dist;
}

static void compute_sprite_screen_x(t_game *game, t_sprite *sprite, float angle_diff)
{
	float screen_x_calc = (game->scene_3d->width / 2.0f) + (angle_diff * game->scene_3d->width) / FOV;

	if (angle_diff > (FOV / 2.0f) || angle_diff < -(FOV / 2.0f))
		sprite->screen_x = -10000;
	else
	{
		if (screen_x_calc < -500)
			screen_x_calc = -500;
		if (screen_x_calc > game->scene_3d->width + 500)
			screen_x_calc = game->scene_3d->width + 500;
		sprite->screen_x = (int)screen_x_calc;
	}
}

static void update_single_sprite(t_game *game, t_sprite *sprite)
{
	float raw_dist, angle_diff;
	compute_sprite_distance(game, sprite, &raw_dist, &angle_diff);
	compute_sprite_screen_x(game, sprite, angle_diff);
}




void	update_sprite_distances(t_game *game)
{
	int	i;

	if (!game || !game->sprites || !game->player || !game->player->img
		|| !game->scene_3d)
		return ;
	i = 0;
	while (i < game->sprites->count)
	{
		if (game->sprites->sprites[i]
			&& game->sprites->sprites[i]->collected == 0)
			update_single_sprite(game, game->sprites->sprites[i]);
		i++;
	}
}
