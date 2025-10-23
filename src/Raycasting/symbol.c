#include "../../cub3D.h"



void draw_key_symbol(mlx_image_t *img, int pixel_x, int pixel_y)
{
    int center_x = pixel_x + MINI_TILE / 2;
    int center_y = pixel_y + MINI_TILE / 2;
    uint32_t *pixels = (uint32_t *)img->pixels;
    int i, j;

    // Draw the key ring (circle)
    for (i = -5; i <= 5; i++)
    {
        for (j = -5; j <= 5; j++)
        {
            if (i * i + j * j <= 16)  // radius^2 = 9 (3px radius)
                pixels[(center_y + j) * img->width + (center_x + i)] = 0xFF0000FF;
        }
    }

    // Draw thicker shaft (rectangle)
    int shaft_length = 8;
    for (i = 0; i < shaft_length; i++)
    {
        for (j = -1; j <= 0; j++) // vertical thickness 3 pixels
        {
            pixels[(center_y + j) * img->width + (center_x + 3 + i)] = 0xFF0000FF;
        }
    }
}

void draw_door_symbol(mlx_image_t *img, int px, int py)
{
    // RRGGBBAA format for MLX42
    uint32_t door_color = 0xFF006400;   // green
    uint32_t knob_color = 0xFF00FFD7;   // gold

    uint32_t *p = (uint32_t *)img->pixels;
    int w = MINI_TILE - 1;
    int h = MINI_TILE - 1;

    // Fill door
    for (int y = 0; y <= h; y++)
        for (int x = 0; x <= w; x++)
            p[(py + y) * img->width + (px + x)] = door_color;

    // Draw bigger knob (circle radius 2)
    int kx = px + MINI_TILE - 4;
    int ky = py + MINI_TILE / 2;
    for (int dy = -2; dy <= 2; dy++)
    {
        for (int dx = -2; dx <= 2; dx++)
        {
            if (dx*dx + dy*dy <= 4) // circle radius^2
                p[(ky + dy) * img->width + (kx + dx)] = knob_color;
        }
    }
}

// void draw_door_symbol(mlx_image_t *img, int pixel_x, int pixel_y)
// {
//     uint32_t *pixels = (uint32_t *)img->pixels;
//     int i, j;

//     for (i = 0; i < MINI_TILE; i++)
//     {
//         for (j = 0; j < MINI_TILE; j++)
//             pixels[(pixel_y + j) * img->width + (pixel_x + i)] = 0xFF006400;
//     }
//     int gap_start = pixel_x + MINI_TILE / 2 - 2;
//     int gap_end = pixel_x + MINI_TILE / 2 + 2;
//     for (i = gap_start; i < gap_end; i++)
//     {
//         for (j = pixel_y + 2; j < pixel_y + MINI_TILE - 2; j++)
//             pixels[j * img->width + i] = 0xFF00FFD7;
//     }
//}
