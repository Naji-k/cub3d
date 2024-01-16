/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:13:56 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/15 14:13:56 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

/// @brief draw a player in specific pos, on player->images
/// @param game 
/// @param pos_x applied when the player moves
/// @param pos_y 
/// @return 
t_error draw_player(t_game *game, float pos_x, float pos_y)
{
	t_player *player;

	player = game->player;
	player->player_image = mlx_new_image(game->mlx, player->size, player->size);
	if (!player->player_image)
		return (ERR_MLX);
	player->fov = 60;
	player->x = pos_x;
	player->y = pos_y;
	player->ray.distance_h = 1000000;
	player->ray.distance_v = 1000000;
	draw_pixels(player->player_image, 0x00bb00FF, player->size);
	if (mlx_image_to_window(game->mlx, player->player_image,  player->x * TILE_SIZE ,  player->y * TILE_SIZE ) < 0)
		return (ERR_MLX);
	find_intersection(game);
	return(OK);
}

t_error find_intersection(t_game *game)
{
	// float			p_x;
	// float			p_y;
	// int x;
	
	// x = 0;
	// p_x = game->player->player_image->instances[0].x + (game->player->size / 2);
	// p_y = game->player->player_image->instances[0].y + (game->player->size / 2);
	game->player->player_lines = mlx_new_image(game->mlx, game->player->ray.screenW, game->player->ray.screenW);
	game->player->wall = mlx_new_image(game->mlx, game->player->ray.screenW, game->player->ray.screenH);
	if (!game->player->player_lines || !game->player->wall)
		return(ERR_MLX);
	if (mlx_image_to_window(game->mlx, game->player->player_lines, 0, 0) < 0)
		return (ERR_MLX);
	if (mlx_image_to_window(game->mlx, game->player->wall, game->player->ray.screenW , 0) < 0)
		return (ERR_MLX);

	return(OK);
}
