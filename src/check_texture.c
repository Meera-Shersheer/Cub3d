#include "../cub3D.h"

void check_file(t_map *map, const char *path, const char *name)
{
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        error_exit(map, name);
    close(fd);
}

void validate_textures(t_map *map)
{
    check_file(map, map->north_texture, "North texture file not found");
    check_file(map, map->south_texture, "South texture file not found");
    check_file(map, map->west_texture,  "West texture file not found");
    check_file(map, map->east_texture,  "East texture file not found");
}
