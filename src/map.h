/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:34:23 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/11 15:58:03 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "MLX42.h"

# include "color.h"

typedef enum e_tile
{
	EMPTY = 0,
	WALL,
	DOOR
}	t_tile;

typedef struct s_map
{
	mlx_texture_t	*north_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	t_color			floor_color;
	t_color			ceiling_color;
	t_tile			**tiles;
}	t_map;

#endif