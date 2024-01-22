/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:13:56 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/22 14:25:23 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>
#include <math.h>
#include <player.h>
#include <stdlib.h>
#include <stdio.h>

/// @brief draw a player on map in specific pos, on player->images,
/// then call ray_casting func()
/// @param game
/// @param pos_x applied when the player moves
/// @param pos_y
/// @return
t_error	draw_player(t_game *game, float pos_x, float pos_y)
{
	t_player	*player;

	player = game->player;
	player->player_image = mlx_new_image(game->mlx, player->size, player->size);
	if (!player->player_image)
		return (ERR_MLX);
	player->fov = 60;
	player->x = pos_x;
	player->y = pos_y;
	player->ray.distance_h = INFINITY;
	player->ray.distance_v = INFINITY;
	// printf("player_rotation=%f\n", player->rotation);
	player->ray.ray_angle = player->rotation + (degree_to_rad(player->fov) / 2);
	// printf("angle=%f\n", player->ray.ray_angle);
	fix_angle(&player->ray.ray_angle);
	if (init_player_images(game) == OK)
	{
		draw_pixels(player->player_image, (t_color){.raw = 0x00bb00FF});
		if (mlx_image_to_window(game->mlx, player->player_image, player->x
			* TILE_SIZE - (player->size / 2), player->y * TILE_SIZE - (player->size / 2)) == -1)
			return (ERR_MLX);
		ray_casting(game->map, player);
	}
	else
		return (ERR_MLX);
	return (OK);
}

/// @brief init images in player struct (player_image, player_lines and wall)
/// to mlx window
/// @param game
/// @return
t_error	init_player_images(t_game *game)
{
	game->player->player_lines = mlx_new_image(game->mlx,
			game->player->ray.screenW, game->player->ray.screenW);
	game->player->wall = mlx_new_image(game->mlx, game->mlx->width,
			game->mlx->height);
	if (!game->player->player_lines || !game->player->wall)
		return (ERR_MLX);
	if (mlx_image_to_window(game->mlx, game->player->wall,
			0, 0) < 0)
		return (ERR_MLX);
	if (create_map(game) != OK)
		return (ERR_MLX);
	if (mlx_image_to_window(game->mlx, game->player->player_lines, 0, 0) < 0)
		return (ERR_MLX);
	return (OK);
}

t_error	ray_casting(t_map *map, t_player *player)
{
	float	p_x;
	float	p_y;
	int		x;
	mlx_texture_t	*texture;
	uint32_t		texture_y;
	uint32_t		texture_x;
	float			step_size;
	t_color			color;
	uint8_t			tmp;

	x = 0;
	p_x = player->x * TILE_SIZE;
	p_y = player->y * TILE_SIZE;
	while (x < player->ray.screenW)
	{
		player->ray.distance_h = INFINITY;
		player->ray.distance_v = INFINITY;
		v_intersection(map, player, p_x, p_y);
		h_intersection(map, player, p_x, p_y);
		if (find_nearest_wall(player) == true)
			draw_line(player->player_lines, (int)p_x, (int)p_y,
				(int)player->ray.end_x, (int)player->ray.end_y, \
				(t_color){.raw = 0xFF0000FF});
		player->ray.lineO = (player->ray.screenH / 2) - (player->ray.lineH / 2);
		draw_line(player->wall, x, 0, x, player->ray.lineO, map->ceiling_color);

		if (player->ray.distance_h < player->ray.distance_v)
		{
			if (player->ray.ray_angle > M_PI)
				texture = map->north_texture;
			else
				texture = map->south_texture;
			texture_x = (uint32_t)((player->ray.end_x  / TILE_SIZE - floorf(player->ray.end_x / TILE_SIZE)) * texture->width);
		}
		else
		{
			if (player->ray.ray_angle >= M_PI * 0.5 && player->ray.ray_angle < M_PI * 1.5)
				texture = map->east_texture;
			else
				texture = map->west_texture;
			texture_x = (uint32_t)((player->ray.end_y  / TILE_SIZE - floorf(player->ray.end_y / TILE_SIZE)) * texture->width);
		}
		step_size = player->ray.lineH / texture->height;
		texture_y = 0;
		while (texture_y < texture->height)
		{
			color = (t_color){.raw = ((int32_t *)texture->pixels)[ \
					texture->height * texture_y + texture_x]};
			tmp = color.a;
			color.a = color.r;
			color.r = tmp;
			tmp = color.b;
			color.b = color.g;
			color.g = tmp;
			draw_line(player->wall, x, \
				player->ray.lineO + step_size * texture_y, x, \
				player->ray.lineO + step_size * texture_y + step_size,
				color);
			texture_y += 1;
		}

		draw_line(player->wall, x, player->ray.lineO + player->ray.lineH, x, \
					player->ray.screenH, map->floor_color);
		
		player->ray.ray_angle -= degree_to_rad(player->fov) / player->ray.screenW;
		fix_angle(&player->ray.ray_angle);
		x++;
	}
	return (OK);
}

/// @brief find the nearest WALL from PLAYER_POS
/// depending on vertical and horizontal intersections (distance_h
/// || distance_v)
/// and calculate that distance ,
/// and calculate wall offset and wall height, fix fish eye problem
/// (happens because the diff between ray angle and player angle)
/// @param player
/// @return if the end on the ray positive return (true || false)
bool	find_nearest_wall(t_player *player)
{
	float	distance;

	distance = -1;
	if (player->ray.distance_h < player->ray.distance_v)
	{
		player->ray.end_x = player->ray.hor_x;
		player->ray.end_y = player->ray.hor_y;
		distance = player->ray.distance_h * cos(player->rotation - player->ray.ray_angle);
		//cal the wall_H
		player->ray.lineH = TILE_SIZE / distance * (player->ray.screenW / tanf(degree_to_rad(player->fov)));
	}
	else
	{
		player->ray.end_x = player->ray.ver_x;
		player->ray.end_y = player->ray.ver_y;
		distance = player->ray.distance_v * cos(player->rotation - player->ray.ray_angle);
		//wall_H
		player->ray.lineH = TILE_SIZE / distance * (player->ray.screenW / tanf(degree_to_rad(player->fov)));
	}
	if (distance > 0)
		return (true);
	return (false);
}
