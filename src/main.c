/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:54:02 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/16 13:38:42 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "MLX42.h"

#include "errors.h"
#include "player.h"
#include "map.h"
#include "parser/parser.h"

int	main(int argc, char *argv[])
{
	t_error		err;
	t_map		map;
	t_player	player;

	if (argc != 2)
	{
		printf("please input exactly 1 map!\n");
		return (1);
	}
	err = parse_file(argv[1], &map, &player);
	if (err != OK)
	{
		printf("Error\nParsing failed: %s!\n", error_string(err));
		return (err);
	}
	if (map_is_closed(&map) == false)
	{
		printf("Error\nThe parsed map is not closed!\n");
		map_destruct(&map);
		return (1);
	}
	map_destruct(&map);
	return (OK);
}
