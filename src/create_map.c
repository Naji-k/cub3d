/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 15:29:16 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/23 15:29:16 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

/// @brief put_pixel for TILES
/// @param img mini_map_image
/// @param color
void	draw_pixels(mlx_image_t *img, t_color color)
{
	size_t	tx;
	size_t	ty;

	tx = 0;
	ty = 0;
	while (ty < img->height)
	{
		while (tx < img->width)
		{
			mlx_put_pixel(img, tx, ty, color.raw);
			tx++;
		}
		tx = 0;
		ty++;
	}
}

static t_color	get_tile_color(t_map *map, size_t x, size_t y)
{
	if (map_get_tile(map, x, y) == TILE_NONE)
		return ((t_color){.a = 0});
	else if (map_get_tile(map, x, y) == TILE_WALL)
		return ((t_color){.r = 31, .g = 31, .b = 31, .a = 255});
	else if (map_get_tile(map, x, y) == TILE_DOOR)
		return ((t_color){.r = 127, .g = 127, .b = 127, .a = 255});
	else if (map_get_tile(map, x, y) == TILE_EMPTY)
		return ((t_color){.r = 255, .g = 255, .b = 255, .a = 255});
	else
		return ((t_color){.r = 255, .g = 0, .b = 0, .a = 255});
}

/// @brief create mini_map_image as (TILE_SIZE = 32)
/// in mlx window by looping in the whole map,
/// make the walls as black, and empty spaces as white
/// @param game
/// @return error when mlx fails || ok
t_error	create_map(t_game *game)
{
	t_color		color;
	size_t		x;
	size_t		y;
	mlx_image_t	*mini_map_image;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			color = get_tile_color(game->map, x, y);
			mini_map_image = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
			if (!mini_map_image)
				return (ERR_MLX);
			draw_pixels(mini_map_image, color);
			if (mlx_image_to_window(game->mlx, mini_map_image, x * (TILE_SIZE),
					y * (TILE_SIZE)) < 0)
				return (ERR_MLX);
			x++;
		}
		y++;
	}
	return (OK);
}
