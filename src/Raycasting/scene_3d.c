/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:45:48 by mshershe          #+#    #+#             */
/*   Updated: 2025/11/02 20:52:21 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_wall_context(t_wall_context *ctx)
{
	static float	tex_pos;

	ctx->wall.wall_height = eval_wall_height(ctx->game, ctx->angle, ctx->rays,
			ctx->col);
	ctx->wall.draw_start = (ctx->game->scene_3d->height / 2)
		- (ctx->wall.wall_height / 2);
	ctx->wall.draw_end = ctx->wall.draw_start + ctx->wall.wall_height;
	if (ctx->wall.draw_start < 0)
		ctx->wall.draw_start = 0;
	if (ctx->wall.draw_end >= (int)ctx->game->scene_3d->height)
		ctx->wall.draw_end = ctx->game->scene_3d->height - 1;
	ctx->tex.img_tex = get_wall_texture(ctx->game, ctx->rays->x, ctx->rays->y);
	if (!ctx->tex.img_tex)
	{
		printf("ERROR: img_tex is NULL!\n");
		return ;
	}
	ctx->wall.tex_x = eval_tex_x(ctx->game, ctx->angle, ctx->rays,
			ctx->tex.img_tex);
	ctx->tex.tex_x = ctx->wall.tex_x;
	ctx->tex.step = (float)ctx->tex.img_tex->height / ctx->wall.wall_height;
	tex_pos = (ctx->wall.draw_start - ctx->game->scene_3d->height / 2
			+ ctx->wall.wall_height / 2) * ctx->tex.step;
	ctx->tex.tex_pos = &tex_pos;
}

static void	draw_floor_ceiling_ctx(t_wall_context *ctx)
{
	color_3d_floor_cielling(ctx->game, ctx->col, ctx->wall.draw_start,
		ctx->wall.draw_end);
}

static void	draw_wall_column_ctx(t_wall_context *ctx)
{
	int			i;
	uint32_t	*pixels;

	pixels = (uint32_t *)ctx->game->scene_3d->pixels;
	i = ctx->wall.draw_start;
	while (i <= ctx->wall.draw_end)
	{
		ctx->tex.screen_y = i;
		pixels[i * ctx->game->scene_3d->width
			+ ctx->col] = get_texture_color(ctx->game, &ctx->tex);
		i++;
	}
}

void	color_3d_scene(t_game *game, int col, t_angle *angle, t_ray_dic *rays)
{
	t_wall_context	ctx;

	if (!game || !game->scene_3d || !rays)
	{
		printf("ERROR: color_3d_scene null pointer!\n");
		return ;
	}
	ctx.game = game;
	ctx.angle = angle;
	ctx.rays = rays;
	ctx.col = col;
	init_wall_context(&ctx);
	draw_floor_ceiling_ctx(&ctx);
	draw_wall_column_ctx(&ctx);
}
