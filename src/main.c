/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:54:02 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/12 17:22:06 by tsteur        ########   odam.nl         */
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

	printf("%i\n", parse_file("maps/example_map.cub", &map, &player));
	printf("%i, %i, %i\n", map.floor_color.r, map.floor_color.g, map.floor_color.b);
	printf("%i, %i, %i\n", map.ceiling_color.r, map.ceiling_color.g, map.ceiling_color.b);
	map_destruct(&map);
	return (OK);
}
