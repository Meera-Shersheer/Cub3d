#include "../../cub3D.h"

void draw_circle( int radius, t_center center, uint32_t color, mlx_image_t *img)
{ 
    int i;
    int j;
    int px;
    int py;
    uint32_t *pixels;

    pixels = (uint32_t *)img->pixels;
    i = -radius;
    while (i <= radius)
    {
        j = -radius;
        while ( j <= radius)
        {
            if (i * i + j * j <= (radius * radius))
            {
                px = center.center_x + i;
                py = center.center_y + j;
                if (px >= 0 && px < (int)img->width && py >= 0 && py < (int)img->height)
                    pixels[py * img->width + px] = color;
            }
            j++;
        }
        i++;
    }
}


void draw_rectangle(t_dimention dim, t_center center, uint32_t color, mlx_image_t *img)
{
    int i;
    int j;
    uint32_t *pixels = (uint32_t *)img->pixels;

    for (i = 0; i < dim.width; i++)
    {
        for (j = 0; j < dim.height; j++)
        {
            int px =  center.center_x + i;
            int py =  center.center_y + j;      
            if (px >= 0 && px < (int)img->width && \
            py >= 0 && py < (int)img->height)
            {
                pixels[py * img->width + px] = color;
            }
        }
    }
}

void draw_key_symbol(mlx_image_t *img, int pixel_x, int pixel_y)
{
    t_center center;
    t_dimention dim;
    int radius = MINI_TILE / 6;
    
    if (!img)
        return;
    center.center_x = pixel_x + MINI_TILE / 2;
    center.center_y = pixel_y + MINI_TILE / 2;
    draw_circle(radius, center, 0xFFDD0000, img);
    dim.width = 2 * radius;
    dim.height = radius / 2;  
    center.center_x += radius ;
    draw_rectangle(dim, center, 0xFFDD0000, img);
}

void draw_door_symbol(mlx_image_t *img, int px, int py)
{
    uint32_t door_color = 0xFF006600;
    uint32_t knob_color = 0xFF00FFD7; 
    t_dimention dim;
    t_center center;

    dim.width = MINI_TILE;
    dim.height = MINI_TILE;
    center.center_x = px;
    center.center_y = py;
    draw_rectangle(dim, center, door_color, img);
    center.center_x = px + MINI_TILE - 4;
    center.center_y = py + MINI_TILE / 2;
    draw_circle(2, center, knob_color, img);
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
