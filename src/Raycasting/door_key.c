#include "../../cub3D.h"


 int pseudo_random(int max)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_usec ^ tv.tv_sec) % max);
}

void place_keys_and_door(t_game *g)
{
	int x, y;
	int num_keys;
	int placed = 0;
	int attempts = 0;
	int max_attempts = 1000;

	num_keys = (pseudo_random(3) + 2);
	g->total_keys = num_keys;
	g->collected_keys = 0;
	g->door_open = 0;
	while (placed < num_keys && attempts < max_attempts)
	{
		y = pseudo_random(g->map->screen_height);
		x = pseudo_random(g->map->screen_width);
		if (g->map->map_lines[y][x] == '0')
		{
			g->map->map_lines[y][x] = 'K';
			placed++;
		}
		attempts++;
	}
	if (placed < num_keys)
		error_exit(NULL, "Cannot place all keys safely");
	attempts = 0;
	while (attempts < max_attempts)
	{
		y = pseudo_random(g->map->screen_height);
		x = pseudo_random(g->map->screen_width);
		if (g->map->map_lines[y][x] == '1')
		{
			if ((x > 0 && g->map->map_lines[y][x - 1] == '0') ||
				(x < g->map->screen_width - 1 && g->map->map_lines[y][x + 1] == '0') ||
				(y > 0 && g->map->map_lines[y - 1][x] == '0') ||
				(y < g->map->screen_height - 1 && g->map->map_lines[y + 1][x] == '0'))
			{
				g->map->map_lines[y][x] = 'D';
				g->door_x = x;
				g->door_y = y;
				break;
			}
		}
		attempts++;
	}
	if (attempts >= max_attempts)
		error_exit(NULL, "Cannot place door safely");
}


void check_key_pickup(t_game *g)
{
    int px = (int)(g->player->x / MINI_TILE);
    int py = (int)(g->player->y / MINI_TILE);

    if (g->map->map_lines[py][px] == 'K')
    {
        g->collected_keys++;
        g->map->map_lines[py][px] = '0';
        printf("🔑 You picked up a key! (%d/%d)\n", g->collected_keys, g->total_keys);
        color_square_map2d(0xFFF3C5B9, g->map_2d, px * MINI_TILE, py * MINI_TILE);
    }
}



void check_door(t_game *g)
{
	int px = (int)(g->player->x / MINI_TILE);
	int py = (int)(g->player->y / MINI_TILE);

	if (g->map->map_lines[py][px] == 'D')
	{
		if (g->collected_keys == g->total_keys)
		{
			printf("🚪 Door opened! You win! 🎉\n");
			g->door_open = 1;
			mlx_close_window(g->mlx);
		}
		else
		{
			printf("🚫 Door is locked! Collect all keys first (%d/%d)\n",
				g->collected_keys, g->total_keys);
		}
	}
}
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

