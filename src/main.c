/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:54:02 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/15 17:25:07 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "player.h"
#include "map.h"
#include "parser/parser.h"

#include <stdio.h>

int	main(void)
{
	t_map		map;
	t_player	player;

	printf("parse error: %i\n", parse_file("maps/example_map.cub", &map, &player));
	printf("map is closed: %s\n", map_is_closed(&map) ? "true" : "false");
	printf("player position: %.1f, %.1f\n", player.x, player.y);
	//printf("%i, %i, %i\n", map.floor_color.r, map.floor_color.g, map.floor_color.b);
	//printf("%i, %i, %i\n", map.ceiling_color.r, map.ceiling_color.g, map.ceiling_color.b);
	printf("map size: %lu, %lu\n", map.width, map.height);
	printf("\n");
	for (size_t y = 0; y < map.height; y++)
	{
		for (size_t x = 0; x < map.width; x++)
		{
			switch (map_get_tile(&map, x, y))
			{
				case TILE_NONE:
				case TILE_EMPTY:
					printf(" ");
					break;
				case TILE_WALL:
					printf("#");
					break;
				default:
					printf("!");
			}
		}
		printf("\n");
	}
	map_destruct(&map);
	return (OK);
}
