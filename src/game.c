/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:32:03 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/23 13:18:06 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <game.h>
#include <math.h>
#include <stdio.h>

/// @brief link map,player,mlx to game struct and create mlx_init with map_width
/// divide it to game 3d and map view
///assign values to player: delta_x, delta_y
/// @param game
/// @param map
/// @param player
/// @return
t_error	init_game(t_game *game)
{
	game->map = &game->map_noptr;
	game->player = &game->player_noptr;
	game->mlx = mlx_init(3 * 16 * 24, \
		2 * 16 * 24, "Map", true);
	if (!game->mlx)
		return (ERR_MLX);
	game->player->delta_x = cos(game->player->rotation) * MOVE_SPEED;
	game->player->delta_y = -sin(game->player->rotation) * MOVE_SPEED;
	game->player->ray.screen_w = game->mlx->width;
	game->player->ray.screen_h = game->mlx->height;
	game->player->size = 16;
	game->player->fov = 60;
	game->player->current_move = NONE;
	game->player->prev_xpos = -1;
	return (OK);
}

void	key_hook(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player->current_move = MOVE_FORWARD;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player->current_move = MOVE_BACKWARD;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player->current_move = MOVE_RIGHT;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player->current_move = MOVE_LEFT;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->current_move = ROTATE_LEFT;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->current_move = ROTATE_RIGHT;
	if (mlx_is_key_down(game->mlx, MLX_KEY_E))
		game->map->doors_opening = !game->map->doors_opening;
	rotate_player(game->player);
	move_player(game->player, game->map);
	game->player->current_move = NONE;
	update(game);
	(void)key;
}

void	loop_hook(void *param)
{
	t_game	*game;

	game = param;
	if (game->map->doors_opening && game->map->doors_state < DOOR_OPENING_TIME)
	{
		game->map->doors_state += game->mlx->delta_time;
		if (game->map->doors_state >= DOOR_OPENING_TIME)
		{
			game->map->doors_open = true;
			game->map->doors_state = DOOR_OPENING_TIME;
		}
		update(game);
	}
	else if (! game->map->doors_opening && game->map->doors_state > 0)
	{
		game->map->doors_state -= game->mlx->delta_time;
		if (game->map->doors_state < DOOR_OPENING_TIME)
			game->map->doors_open = false;
		if (game->map->doors_state < 0)
			game->map->doors_state = 0;
		update(game);
	}
}

void	update(t_game *game)
{
	draw_pixels(game->player->player_lines, (t_color){.a = 0});
	game->player->player_image->instances[0].x = game->player->x \
		* TILE_SIZE - TILE_SIZE / 2;
	game->player->player_image->instances[0].y = game->player->y \
		* TILE_SIZE - TILE_SIZE / 2;
	game->player->ray.ray_angle = game->player->rotation \
		+ (degree_to_rad(game->player->fov) / 2);
	fix_angle(&game->player->ray.ray_angle);
	ray_casting(game->map, game->player);
}
