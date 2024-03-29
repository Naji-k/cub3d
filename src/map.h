/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:34:23 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/23 11:44:04 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "MLX42.h"
# include "color.h"
# include <stdbool.h>
# include <stddef.h>

# define DOOR_OPENING_TIME 1.0

typedef struct s_game	t_game;
typedef enum e_tile
{
	TILE_NONE = 0,
	TILE_EMPTY,
	TILE_WALL,
	TILE_DOOR
}						t_tile;

typedef struct s_map
{
	mlx_texture_t		*north_texture;
	mlx_texture_t		*east_texture;
	mlx_texture_t		*south_texture;
	mlx_texture_t		*west_texture;
	mlx_texture_t		*door1_texture;
	mlx_texture_t		*door2_texture;
	mlx_texture_t		*door3_texture;
	t_color				floor_color;
	t_color				ceiling_color;
	size_t				width;
	size_t				height;
	bool				doors_open;
	bool				doors_opening;
	float				doors_state;
	t_tile				*tiles;
}						t_map;

void					map_destruct(t_map *map);
void					map_set_tile(t_map *map, unsigned long x,
							unsigned long y, t_tile tile);
t_tile					map_get_tile(t_map *map, unsigned long x,
							unsigned long y);
bool					map_is_tile_on_edge(t_map *map, unsigned long x,
							unsigned long y);
bool					map_is_closed(t_map *map);
t_error					create_map(t_game *game);

#endif