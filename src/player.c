/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:13:56 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/23 16:22:28 by tsteur        ########   odam.nl         */
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
t_error	draw_player(t_game *game)
{
	t_player	*player;

	player = game->player;
	player->player_image = mlx_new_image(game->mlx, player->size, player->size);
	if (!player->player_image)
		return (ERR_MLX);
	player->fov = 60;
	player->ray.distance_h = INFINITY;
	player->ray.distance_v = INFINITY;
	player->ray.ray_angle = player->rotation + (degree_to_rad(player->fov) / 2);
	fix_angle(&player->ray.ray_angle);
	if (init_player_images(game) == OK)
	{
		draw_pixels(player->player_image, (t_color){.raw = 0x00bb00FF});
		if (game->map->width < 24 && game->map->height < 24 && \
			mlx_image_to_window(game->mlx, player->player_image, player->x
				* TILE_SIZE - (player->size / 2), player->y * TILE_SIZE - \
				(player->size / 2)) == -1)
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
			game->player->ray.screen_w, game->player->ray.screen_w);
	game->player->wall = mlx_new_image(game->mlx, game->mlx->width,
			game->mlx->height);
	if (!game->player->player_lines || !game->player->wall)
		return (ERR_MLX);
	if (mlx_image_to_window(game->mlx, game->player->wall,
			0, 0) < 0)
		return (ERR_MLX);
	if (game->map->width < 24 && game->map->height < 24 && \
			create_map(game) != OK)
		return (ERR_MLX);
	if (game->map->width < 24 && game->map->height < 24 && \
		mlx_image_to_window(game->mlx, game->player->player_lines, 0, 0) < 0)
		return (ERR_MLX);
	return (OK);
}

void	select_texture(t_map *map, t_player *player, mlx_texture_t **texture, \
						uint32_t *texture_x)
{
	*texture = map->west_texture;
	if (player->ray.ray_angle >= M_PI * 0.5 && \
		player->ray.ray_angle < M_PI * 1.5)
		*texture = map->east_texture;
	*texture_x = (uint32_t)((player->ray.end_y / TILE_SIZE - \
			floorf(player->ray.end_y / TILE_SIZE)) * (*texture)->width);
	if (player->ray.distance_h < player->ray.distance_v)
	{
		*texture = map->south_texture;
		if (player->ray.ray_angle > M_PI)
			*texture = map->north_texture;
		*texture_x = (uint32_t)((player->ray.end_x / TILE_SIZE - \
				floorf(player->ray.end_x / TILE_SIZE)) * (*texture)->width);
	}
	if (player->ray.hit_tile == TILE_DOOR)
	{
		*texture = map->door3_texture;
		if (map->doors_state == 0)
			*texture = map->door1_texture;
		else if (map->doors_state > 0 && \
			map->doors_state <= DOOR_OPENING_TIME / 2)
			*texture = map->door2_texture;
	}
}

void	draw_slice(t_map *map, t_player *player, int x)
{
	mlx_texture_t	*texture;
	uint32_t		texture_y;
	uint32_t		texture_x;
	float			step_size;
	t_color			color;

	draw_line(player->wall, (int [2]){x, 0}, \
		(int [2]){x, player->ray.line_offset}, map->ceiling_color);
	draw_line(player->wall, \
		(int [2]){x, player->ray.line_offset + player->ray.line_h}, \
		(int [2]){x, player->ray.screen_h}, map->floor_color);
	select_texture(map, player, &texture, &texture_x);
	step_size = player->ray.line_h / texture->height;
	texture_y = 0;
	while (texture_y < texture->height)
	{
		color = (t_color){.raw = ((int32_t *)texture->pixels)[\
				texture->height * texture_y + texture_x]};
		color = swap_rgba_abgr(color);
		draw_line(player->wall, (int [2]){x, player->ray.line_offset + \
			step_size * texture_y}, (int [2]){x, player->ray.line_offset + \
			step_size * texture_y + step_size}, color);
		texture_y += 1;
	}
}

void	ray_casting(t_map *map, t_player *player)
{
	float			p_x;
	float			p_y;
	int				x;

	x = 0;
	p_x = player->x * TILE_SIZE;
	p_y = player->y * TILE_SIZE;
	while (x < player->ray.screen_w)
	{
		player->ray.distance_h = INFINITY;
		player->ray.distance_v = INFINITY;
		v_intersection(map, player, p_x, p_y);
		h_intersection(map, player, p_x, p_y);
		find_nearest_wall(player);
		draw_line(player->player_lines, (int [2]){p_x, p_y}, (int [2]){
			player->ray.end_x, player->ray.end_y}, \
			(t_color){.raw = 0xFF0000FF});
		player->ray.line_offset = (player->ray.screen_h / 2) - \
				(player->ray.line_h / 2);
		draw_slice(map, player, x);
		player->ray.ray_angle -= degree_to_rad(player->fov) / \
				player->ray.screen_w;
		fix_angle(&player->ray.ray_angle);
		x++;
	}
}
