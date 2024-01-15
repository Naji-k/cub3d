/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:32:03 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/15 14:32:03 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <MLX42.h>
#include <player.h>

/// @brief put_pixel for TILES 
/// @param img mini_map_image
/// @param color 
void	draw_pixels(mlx_image_t *img, uint32_t color, size_t size)
{
	size_t			tx;
	size_t			ty;
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
/// @brief create mini_map_image as (TILE_SIZE = 32) in mlx window by looping in the whole map,
/// make the walls as black, and empty spaces as white
/// @param game 
/// @param x 0, base point to the map just to save some lines
/// @param y 0, base point to the map just to save some lines
/// @return error when mlx fails || ok
t_error	create_map(t_game *game, size_t x, size_t y)
{
	uint32_t color;
	mlx_image_t *mini_map_image;

	while (y < game->map->height)
	{
		while (x < game->map->width)
		{
			if (map_get_tile(game->map, x, y) == TILE_WALL)
				color = 0xFF000000;
			else
				color = 0xFFFFFFFF;
			mini_map_image = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
			if (!mini_map_image)
				return (ERR_MLX);
			draw_pixels(mini_map_image, color, TILE_SIZE);
			if (mlx_image_to_window(game->mlx, mini_map_image, x * (TILE_SIZE),y * (TILE_SIZE)) < 0)
				return (ERR_MLX);
			x++;
		}
		x = 0;
		y++;
	}
	return (OK);
}
/// @brief link map,player,mlx to game struct and create mlx_init with map_width * 2 
/// divide it to game 3d and map view
///assign values to player: delta_x, delta_y
/// @param game 
/// @param map 
/// @param player 
/// @return 
t_error init_game(t_game *game, t_map *map, t_player *player)
{
	game->map = map;
	game->player = player;
	game->mlx = mlx_init(2 * (TILE_SIZE)*game->map->width, (TILE_SIZE)*game->map->height, "Map", true);
	if (!game->mlx)
		return (ERR_MLX);
	game->player->delta_x = cos(player->rotation) * 5;
	game->player->delta_y = -sin(player->rotation) * 5;
	game->player->ray.screenW = map->width * TILE_SIZE;
	game->player->ray.screenH = map->height * TILE_SIZE;
	game->player->size = 16;
	game->player->fov = 60;
	return (OK);
}
