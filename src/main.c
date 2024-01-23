/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:54:02 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/23 12:06:07 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "MLX42.h"

#include "errors.h"
#include "game.h"
#include "map.h"
#include "parser/parser.h"

t_error	cub3d(t_game *game)
{
	t_error		err;

	err = init_game(game);
	if (err != OK)
	{
		mlx_terminate(game->mlx);
		return (err);
	}
	err = draw_player(game);
	if (err != OK)
	{
		mlx_terminate(game->mlx);
		return (err);
	}
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, loop_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (OK);
}

int	main(int argc, char *argv[])
{
	t_error		err;
	t_game		game;

	if (argc != 2)
	{
		printf("Error\nplease input exactly 1 map!\n");
		return (1);
	}
	err = parse_file(argv[1], &game.map_noptr, &game.player_noptr);
	if (err != OK)
	{
		printf("Error\nParsing failed: %s!\n", error_string(err));
		return (err);
	}
	if (map_is_closed(&game.map_noptr) == false)
	{
		printf("Error\nThe parsed map is not closed!\n");
		map_destruct(&game.map_noptr);
		return (1);
	}
	err = cub3d(&game);
	map_destruct(&game.map_noptr);
	if (err != OK)
		printf("Error\nInitializing failed: %s!\n", error_string(err));
	return (err);
}
