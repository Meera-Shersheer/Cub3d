/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshershe <mshershe@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:32:11 by mshershe          #+#    #+#             */
/*   Updated: 2025/09/09 16:04:25 by mshershe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./Libft/ft_printf.h"
# include "./Libft/get_next_line_bonus.h"
# include "./Libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "MLX42/include/MLX42/MLX42.h"
# include <string.h>

int check_arg(char *map_file);

#endif