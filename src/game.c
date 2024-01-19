/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:32:03 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/19 15:51:38 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <game.h>
#include <math.h>
#include <stdio.h>

/// @brief put_pixel for TILES
/// @param img mini_map_image
/// @param color
void	draw_pixels(mlx_image_t *img, t_color color, size_t size)
{
	size_t		tx;
	size_t		ty;
	t_color		og_color;

	tx = 0;
	ty = 0;
	og_color = color;
	while (ty < size)
	{
		while (tx < size)
		{
			mlx_put_pixel(img, tx, ty, color.raw);
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
t_error	create_map(t_game *game)
{
	t_color	color;
	mlx_image_t	*mini_map_image;
	size_t x;
	size_t y;
	
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (map_get_tile(game->map, x, y) == TILE_NONE)
				color  = (t_color){.a = 0};
			else if (map_get_tile(game->map, x, y) == TILE_WALL)
				color = (t_color){.r=31, .g=31, .b=31, .a = 255};
			else if (map_get_tile(game->map, x, y) == TILE_DOOR)
				color = (t_color){.r=127, .g=127, .b=127, .a = 255};
			else if (map_get_tile(game->map, x, y) == TILE_EMPTY)
				color = (t_color){.r=255, .g=255, .b=255, .a = 255};
			else
				color = (t_color){.r=255, .g=0, .b=0, .a = 255};
			mini_map_image = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
			if (!mini_map_image)
				return (ERR_MLX);
			draw_pixels(mini_map_image, color, TILE_SIZE);
			if (mlx_image_to_window(game->mlx, mini_map_image, x * (TILE_SIZE),
					y * (TILE_SIZE)) < 0)
				return (ERR_MLX);
			x++;
		}
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
	game->mlx = mlx_init(3 * (TILE_SIZE) * 24, \
		2 * (TILE_SIZE) * 24, "Map", true);
	if (!game->mlx)
		return (ERR_MLX);
	game->player->delta_x = cos(player->rotation) * 5;
	game->player->delta_y = -sin(player->rotation) * 5;
	game->player->ray.screenW = game->mlx->width;
	game->player->ray.screenH = game->mlx->height;
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
	printf("playerOld x=%f y=%f\n deltaX=%f deltaY=%f\n", player->x, player->y, player->delta_x, player->delta_y);
	if (player->current_move == MOVE_FORWARD)
	{
		player->y += player->delta_y;
		player->x += player->delta_x;
	}
	if (player->current_move == MOVE_BACKWARD)
	{
		player->y -= player->delta_y;
		player->x -= player->delta_x;
	}
	printf("playerNEW x=%f y=%f\n", player->x, player->y);
}
void rotate_player(t_player *player)
{
	if (player->current_move == ROTATE_LEFT)
		player->rotation -= 0.1;
	if (player->current_move == ROTATE_RIGHT)
		player->rotation += 0.1;
	fix_angle(&player->rotation);
	player->delta_x = cos(player->rotation) * 0.3;
	player->delta_y = -sin(player->rotation) * 0.3;
}
void	game_loop(t_game *game)
{
	mlx_delete_image(game->mlx, game->player->wall);
	mlx_delete_image(game->mlx, game->player->player_lines);
	mlx_delete_image(game->mlx, game->player->player_image);
	draw_player(game, game->player->x, game->player->y);
}
