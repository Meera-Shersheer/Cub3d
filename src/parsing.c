#include "cub3d.h"

void classify_textures_and_colors(char *line, t_map *map)
{
    if (line[0] == 'R' && line[1] == ' ')
    {
        map->screen_width = ft_atoi(line + 2);
        map->screen_height = ft_atoi(ft_strchr(line + 2, ' '));
    }
    else if (line[0] == 'N' && line[1] == 'O')
        map->north_texture = line + 3;
    else if (line[0] == 'S' && line[1] == 'O')
        map->south_texture = line + 3;
    else if (line[0] == 'W' && line[1] == 'E')
        map->west_texture = line + 3;
    else if (line[0] == 'E' && line[1] == 'A')
        map->east_texture = line + 3;
    else if (line[0] == 'S' && line[1] == ' ')
        map->sprite_texture = line + 2;
    else if (line[0] == 'F')
        map->floor_color = line + 2;
    else if (line[0] == 'C')
        map->ceiling_color = line + 2;
}

void classify_map_lines(char **lines, t_map *map)
{
    size_t i ;
    size_t map_index;
    
    i = 0;
    map_index = 0;
    while (lines[i])
    {
        if (lines[i][0] != 'R' && lines[i][0] != 'N' && lines[i][0] != 'S' &&
            lines[i][0] != 'W' && lines[i][0] != 'E' && lines[i][0] != 'F' &&
            lines[i][0] != 'C')
        {
            map->map_lines[map_index] = lines[i];
            map_index++;
        }
        else
        {
            classify_textures_and_colors(lines[i], map);
        }
        i++;
    }
    map->map_lines[map_index] = NULL;
}
void classify_lines(char **lines, t_map *map)
{
    size_t i = 0;
    while (lines[i])
    {
        classify_textures_and_colors(lines[i], map);
        i++;
    }

    classify_map_lines(lines, map);
}
