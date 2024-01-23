/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 12:38:29 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/23 11:40:44 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#include "MLX42.h"

#include "map.h"

void	map_destruct(t_map *map)
{
	if (map->north_texture != NULL)
		mlx_delete_texture(map->north_texture);
	if (map->east_texture != NULL)
		mlx_delete_texture(map->east_texture);
	if (map->south_texture != NULL)
		mlx_delete_texture(map->south_texture);
	if (map->west_texture != NULL)
		mlx_delete_texture(map->west_texture);
	if (map->door1_texture != NULL)
		mlx_delete_texture(map->door1_texture);
	if (map->door2_texture != NULL)
		mlx_delete_texture(map->door2_texture);
	if (map->door3_texture != NULL)
		mlx_delete_texture(map->door3_texture);
	if (map->tiles != NULL)
		free(map->tiles);
}

void	map_set_tile(t_map *map, unsigned long x, unsigned long y, t_tile tile)
{
	if (x >= 0 && x < map->width && y >= 0 && y < map->height)
		map->tiles[y * map->width + x] = tile;
}

t_tile	map_get_tile(t_map *map, unsigned long x, unsigned long y)
{
	if (x >= 0 && x < map->width && y >= 0 && y < map->height)
		return (map->tiles[y * map->width + x]);
	return (TILE_NONE);
}

bool	map_is_tile_on_edge(t_map *map, unsigned long x, unsigned long y)
{
	if (x <= 0)
		return (true);
	if (x >= map->width - 1)
		return (true);
	if (y <= 0)
		return (true);
	if (y >= map->height - 1)
		return (true);
	if (map_get_tile(map, x - 1, y) == TILE_NONE)
		return (true);
	if (map_get_tile(map, x + 1, y) == TILE_NONE)
		return (true);
	if (map_get_tile(map, x, y - 1) == TILE_NONE)
		return (true);
	if (map_get_tile(map, x, y + 1) == TILE_NONE)
		return (true);
	return (false);
}

bool	map_is_closed(t_map *map)
{
	unsigned long	x;
	unsigned long	y;
	t_tile			tile;

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			tile = map_get_tile(map, x, y);
			if (tile != TILE_WALL && tile != TILE_NONE)
				if (map_is_tile_on_edge(map, x, y))
					return (false);
			y++;
		}
		x++;
	}
	return (true);
}
