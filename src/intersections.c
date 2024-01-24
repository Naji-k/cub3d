/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersections.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 15:48:20 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/24 11:14:12 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>
#include <math.h>
#include <stdio.h>

void	h_calculations(t_ray *ray, float p_x, float p_y, double angle)
{
	float	yn;
	float	xn;

	if (fabs(angle) < 0.0001 || fabs(angle - M_PI) < 0.0001)
		return ;
	if (angle > 0 && angle < M_PI)
	{
		yn = (((int)p_y >> sizeof(TILE_SIZE)) << sizeof(TILE_SIZE)) - 0.01;
		ray->ys = -TILE_SIZE;
	}
	else
	{
		yn = (((int)p_y >> sizeof(TILE_SIZE)) << sizeof(TILE_SIZE)) + TILE_SIZE;
		ray->ys = TILE_SIZE;
	}
	xn = (p_y - yn) / tan(angle) + p_x;
	ray->xs = ray->ys / tan(angle);
	if (((angle > 0 && angle < 0.5 * M_PI) || (angle > 1.5 * M_PI))
		&& ray->xs < 0)
		ray->xs *= -1;
	else if (((angle >= 0.5 * M_PI && angle <= 1.5 * M_PI))
		&& ray->xs > 0)
		ray->xs *= -1;
	ray->y_target = yn;
	ray->x_target = xn;
}

float	h_intersection(t_map *map, t_player *player, float p_x, float p_y)
{
	t_ray	*ray;

	ray = &player->ray;
	h_calculations(ray, p_x, p_y, ray->ray_angle);
	while (1)
	{
		if (ray->x_target < 0 || ray->y_target < 0
			|| ray->y_target / TILE_SIZE >= map->height
			|| ray->x_target / TILE_SIZE >= map->width)
			break ;
		if (is_ray_hit_wall(map, ray) == true)
		{
			ray->distance_h = dist(p_x, p_y, ray->x_target,
					ray->y_target);
			ray->hor_x = ray->x_target;
			ray->hor_y = ray->y_target;
			ray->hit_tile_h = map_get_tile(map, ray->x_target
					/ TILE_SIZE, ray->y_target / TILE_SIZE);
			return (ray->distance_h);
		}
		ray->y_target += ray->ys;
		ray->x_target += ray->xs;
	}
	return (INFINITY);
}

void	v_calculations(t_ray *ray, float p_x, float p_y, double angle)
{
	float	yn;
	float	xn;

	if ((fabs(angle - 0.5 * M_PI) < 0.0001) || (fabs(angle - (1.5
					* M_PI)) < 0.0001))
		return ;
	if ((angle >= 0.5 * M_PI && angle < 1.5 * M_PI))
	{
		xn = (((int)p_x >> sizeof(TILE_SIZE)) << sizeof(TILE_SIZE)) - 0.01;
		ray->xs = -TILE_SIZE;
	}
	else
	{
		xn = (((int)p_x >> sizeof(TILE_SIZE)) << sizeof(TILE_SIZE)) + TILE_SIZE;
		ray->xs = TILE_SIZE;
	}
	yn = (p_x - xn) * tan(angle) + p_y;
	ray->ys = ray->xs * tan(angle);
	if (angle > 0 && angle < M_PI && ray->ys > 0)
		ray->ys *= -1;
	else if (angle > M_PI && ray->ys < 0)
		ray->ys *= -1;
	ray->y_target = yn;
	ray->x_target = xn;
}

float	v_intersection(t_map *map, t_player *player, float p_x, float p_y)
{
	t_ray	*ray;

	ray = &player->ray;
	v_calculations(ray, p_x, p_y, player->ray.ray_angle);
	while (1)
	{
		if (ray->x_target < 0 || ray->y_target < 0
			|| ray->y_target / TILE_SIZE >= map->height
			|| ray->x_target / TILE_SIZE >= map->width)
			break ;
		if (is_ray_hit_wall(map, ray) == true)
		{
			ray->distance_v = dist(p_x, p_y, ray->x_target,
					ray->y_target);
			ray->ver_x = ray->x_target;
			ray->ver_y = ray->y_target;
			ray->hit_tile_v = map_get_tile(map, ray->x_target
					/ TILE_SIZE, ray->y_target / TILE_SIZE);
			return (ray->distance_v);
		}
		ray->y_target += ray->ys;
		ray->x_target += ray->xs;
	}
	return (INFINITY);
}
