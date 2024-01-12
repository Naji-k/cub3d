/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 12:38:29 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/12 17:07:26 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
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
	if (map->tiles != NULL)
		free(map->tiles);
}

void map_set_tile(t_map *map, unsigned long x, unsigned long y, t_tile tile)
{
	map->tiles[y * map->width + x] = tile;
}

t_tile map_get_tile(t_map *map, unsigned long x, unsigned long y)
{
	return (map->tiles[y * map->width + x]);
}
