/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalmahas <aalmahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:09:02 by aalmahas          #+#    #+#             */
/*   Updated: 2025/10/03 15:14:53 by aalmahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_corners	get_corners(t_game *g, float nx, float ny)
{
	t_corners	c;
	int			player_width;
	int			player_height;

	player_width = g->player->img->width;
	player_height = g->player->img->height;
	c.rows = 0;
	while (g->map->map_lines[c.rows])
		c.rows++;
	c.corners_x[0] = (int)(nx / WIDTH);
	c.corners_x[1] = (int)((nx + player_width - 1) / WIDTH);
	c.corners_y[0] = (int)(ny / HEIGHT);
	c.corners_y[1] = (int)((ny + player_height - 1) / HEIGHT);
	return (c);
}

int	is_out_of_bounds(t_game *g, int row, int col)
{
	int	rows;

	rows = 0;
	while (g->map->map_lines[rows])
		rows++;
	if (row >= rows)
		return (1);
	if (col >= (int)ft_strlen(g->map->map_lines[row]))
		return (1);
	return (0);
}

int	is_wall_at(t_game *g, int row, int col)
{
	if (g->map->map_lines[row][col] == '1')
		return (1);
	return (0);
}

int	can_move(t_game *g, t_corners c)
{
	int	can_move;
	int	i;
	int	j;

	can_move = 1;
	i = 0;
	while (i < 2 && can_move)
	{
		j = 0;
		while (j < 2 && can_move)
		{
			if (is_out_of_bounds(g, c.corners_y[j], c.corners_x[i])
				|| is_wall_at(g, c.corners_y[j], c.corners_x[i]))
				can_move = 0;
			j++;
		}
		i++;
	}
	return (can_move);
}

void	try_move(t_game *g, float dx, float dy)
{
	float		nx;
	float		ny;
	t_corners	c;
	int			final_row;
	int			final_col;

	nx = g->player->x + dx;
	ny = g->player->y + dy;
	c = get_corners(g, nx, g->player->y);
	if (can_move(g, c))
		g->player->x = nx;
	c = get_corners(g, g->player->x, ny);
	if (can_move(g, c))
		g->player->y = ny;
	final_row = (int)(g->player->y / HEIGHT);
	final_col = (int)(g->player->x / WIDTH);
	printf("Player stopped at map cell -> row: %d, col: %d, value: %c\n",
		final_row, final_col, g->map->map_lines[final_row][final_col]);
}
