/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 15:25:38 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/24 11:10:12 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>
#include <math.h>

bool	is_ray_hit_wall(t_map *map, t_ray *ray)
{
	if (map_get_tile(map, ray->x_target / TILE_SIZE, ray->y_target
			/ TILE_SIZE) != TILE_EMPTY
		&& !(map_get_tile(map, ray->x_target / TILE_SIZE, ray->y_target
				/ TILE_SIZE) == TILE_DOOR && map->doors_open))
		return (true);
	return (false);
}

void	find_nearest_wall(t_player *player)
{
	float	distance;

	if (player->ray.distance_h < player->ray.distance_v)
	{
		player->ray.end_x = player->ray.hor_x;
		player->ray.end_y = player->ray.hor_y;
		distance = player->ray.distance_h * \
			cos(player->rotation - player->ray.ray_angle);
		player->ray.line_h = TILE_SIZE / distance * \
			(player->ray.screen_w / tanf(degree_to_rad(player->fov)));
		player->ray.hit_tile = player->ray.hit_tile_h;
	}
	else
	{
		player->ray.end_x = player->ray.ver_x;
		player->ray.end_y = player->ray.ver_y;
		distance = player->ray.distance_v * \
			cos(player->rotation - player->ray.ray_angle);
		player->ray.line_h = TILE_SIZE / distance * \
			(player->ray.screen_w / tanf(degree_to_rad(player->fov)));
		player->ray.hit_tile = player->ray.hit_tile_v;
	}
}
