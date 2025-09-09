#include "../cub3D.h"

int parse_color_line(const char *line, t_color *color)
{
    char *tmp = (char *)line;
    int r, g, b;

    if (!ft_isdigit(*tmp))
        return (1);
    r = ft_atoi(tmp);
    while (*tmp && *tmp != ',') tmp++;
    if (*tmp != ',') return (1);
    tmp++;

    if (!ft_isdigit(*tmp))
        return (1);
    g = ft_atoi(tmp);
    while (*tmp && *tmp != ',') tmp++;
    if (*tmp != ',') return (1);
    tmp++;

    if (!ft_isdigit(*tmp))
        return (1);
    b = ft_atoi(tmp);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (1);

    color->r = r;
    color->g = g;
    color->b = b;
    return (0);
}

