/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 16:16:01 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/09 17:28:12 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/*
Test list :
 valgrind ./cub3D fg
 valgrind ./cub3D fg.cu
valgrind ./cub3D fg.cub.cub




*/

int main(void)
{
    mlx_t *mlx = mlx_init(800, 600, "Test MLX42", true);
    if (!mlx)
        return (1);

    mlx_image_t *img = mlx_new_image(mlx, 800, 600);
    for (int y = 0; y < 600; y++)
        for (int x = 0; x < 800; x++)
            mlx_put_pixel(img, x, y, 0xFF0000FF);

    mlx_image_to_window(mlx, img, 0, 0);
    mlx_loop(mlx);
    return (0);
}
