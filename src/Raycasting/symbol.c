#include "../../cub3D.h"



void draw_key_symbol(mlx_image_t *img, int pixel_x, int pixel_y)
{
    int center_x = pixel_x + MINI_TILE / 2;
    int center_y = pixel_y + MINI_TILE / 2;
    uint32_t *pixels = (uint32_t *)img->pixels;
    int i, j;
    for (i = -2; i <= 2; i++)
    {
        for (j = -2; j <= 2; j++)
        {
            if (i * i + j * j <= 4)
                pixels[(center_y + j) * img->width + (center_x + i)] = 0xFFFFFF00;
        }
    }
    for (i = 0; i < 5; i++)
        pixels[center_y * img->width + (center_x + 3 + i)] = 0xFFFFFF00;
}
void draw_door_symbol(mlx_image_t *img, int pixel_x, int pixel_y)
{
    uint32_t *pixels = (uint32_t *)img->pixels;
    int i, j;

    for (i = 0; i < MINI_TILE; i++)
    {
        for (j = 0; j < MINI_TILE; j++)
            pixels[(pixel_y + j) * img->width + (pixel_x + i)] = 0xFF230C06;
    }
    int gap_start = pixel_x + MINI_TILE / 2 - 2;
    int gap_end = pixel_x + MINI_TILE / 2 + 2;
    for (i = gap_start; i < gap_end; i++)
    {
        for (j = pixel_y + 2; j < pixel_y + MINI_TILE - 2; j++)
            pixels[j * img->width + i] = 0xFFAAAAAA;
    }
}