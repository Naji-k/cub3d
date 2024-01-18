/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:32:03 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/18 13:11:00 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <game.h>
#include <math.h>
#include <stdio.h>

/// @brief put_pixel for TILES
/// @param img mini_map_image
/// @param color
void	draw_pixels(mlx_image_t *img, uint32_t color, size_t size)
{
	size_t		tx;
	size_t		ty;
	uint32_t	og_color;

	tx = 0;
	ty = 0;
	og_color = color;
	while (ty < size)
	{
		while (tx < size)
		{
			if (ty == size - 1 || tx == 0)
				color = 0x000022FF;
			else
				color = og_color;
			mlx_put_pixel(img, tx, ty, color);
			tx++;
		}
		tx = 0;
		ty++;
	}
}

/// @brief create mini_map_image as (TILE_SIZE = 32)
/// in mlx window by looping in the whole map,
/// make the walls as black, and empty spaces as white
/// @param game
/// @param x 0, base point to the map just to save some lines
/// @param y 0, base point to the map just to save some lines
/// @return error when mlx fails || ok
t_error	create_map(t_game *game, size_t x, size_t y)
{
	uint32_t	color;
	mlx_image_t	*mini_map_image;

	while (y < game->map->height)
	{
		while (x < game->map->width)
		{
			if (map_get_tile(game->map, x, y) == TILE_WALL
				|| map_get_tile(game->map, x, y) == TILE_NONE)
				color = 0xFF000000;
			else
				color = 0xFFFFFFFF;
			mini_map_image = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
			if (!mini_map_image)
				return (ERR_MLX);
			draw_pixels(mini_map_image, color, TILE_SIZE);
			if (mlx_image_to_window(game->mlx, mini_map_image, x * (TILE_SIZE),
					y * (TILE_SIZE)) < 0)
				return (ERR_MLX);
			x++;
		}
		x = 0;
		y++;
	}
	return (OK);
}

/// @brief link map,player,mlx to game struct and create mlx_init with map_width
/// divide it to game 3d and map view
///assign values to player: delta_x, delta_y
/// @param game
/// @param map
/// @param player
/// @return
t_error	init_game(t_game *game, t_map *map, t_player *player)
{
	t_move_direction player_move;

	player_move = NONE;
	game->map = map;
	game->player = player;
	game->mlx = mlx_init(2 * (TILE_SIZE) * game->map->width, \
		(TILE_SIZE) * game->map->height, "Map", true);
	if (!game->mlx)
		return (ERR_MLX);
	game->player->delta_x = cos(player->rotation) * 5;
	game->player->delta_y = -sin(player->rotation) * 5;
	game->player->ray.screenW = map->width * TILE_SIZE;
	game->player->ray.screenH = map->height * TILE_SIZE;
	game->player->size = 16;
	game->player->fov = 60;
	game->player->current_move = player_move;
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->current_move = ROTATE_RIGHT;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->current_move = ROTATE_LEFT;
	rotate_player(game->player);
	move_player(game->player);
	game->player->current_move = NONE;
	game_loop(game);
	(void)key;
}

void move_player(t_player *player)
{
	float		x;
	float		y;

	printf("playerOld x=%f y=%f\n deltaX=%f deltaY=%f\n", player->x, player->y, player->delta_x, player->delta_y);
	x = player->player_image->instances[0].x;
	y = player->player_image->instances[0].y;
	if (player->current_move == MOVE_FORWARD || player->current_move == MOVE_BACKWARD)
	{
		if (player->current_move == MOVE_FORWARD)
		{
			y += player->delta_y;
			x += player->delta_x;
		}
		if (player->current_move == MOVE_BACKWARD)
		{
			y -= player->delta_y;
			x -= player->delta_x;
		}
		player->x = x / TILE_SIZE;
		player->y = y / TILE_SIZE;
		printf("playerNEW x=%f y=%f\n", player->x, player->y);
	}
}
void rotate_player(t_player *player)
{
	if (player->current_move == ROTATE_LEFT || player->current_move == ROTATE_RIGHT)
	{
		if (player->current_move == ROTATE_LEFT)
		{
			player->rotation += 0.1;
			if (player->rotation >= 2 * M_PI)
				player->rotation -= 2 *M_PI;
		} else if (player->current_move == ROTATE_RIGHT)
		{
			player->rotation -= 0.1;
			if (player->rotation <= 0)
				player->rotation += (2 * M_PI);
		}
		player->delta_x = cos(player->rotation) * 5;
		player->delta_y = -sin(player->rotation) * 5;
	}
}
void	game_loop(t_game *game)
{
	mlx_delete_image(game->mlx, game->player->wall);
	mlx_delete_image(game->mlx, game->player->player_lines);
	mlx_delete_image(game->mlx, game->player->player_image);
	draw_player(game, game->player->x, game->player->y);
}
