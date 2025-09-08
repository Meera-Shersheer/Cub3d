#include "MLX42/MLX42.h"

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
