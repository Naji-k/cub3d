/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersections.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 15:48:20 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/22 16:22:12 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>
#include <math.h>
#include <stdio.h>

float h_intersection(t_map *map,t_player *player, float p_x, float p_y)
{
	float ys;
	float xs;
	float yn;
	float xn;
	double angle;
	float x_target;
	float y_target;

	angle = player->ray.ray_angle;
	if (fabs(angle - 0) < 0.0001 || fabs(angle - M_PI) < 0.0001) 
	{
		xn = p_x;
		yn = p_y;
		return (INFINITY);
	}
	if (angle > 0 && angle < M_PI_2)
	{//Q1
		yn = (((int)p_y >> sizeof(TILE_SIZE)) << sizeof(TILE_SIZE) ) - 0.1; 
		xn = (p_y - yn)/tan(angle) + p_x;
		ys = -TILE_SIZE;
		xs = ys / tan(angle);
		xs *= xs > 0 ? 1 : -1;
	}
	else if (angle >= 0.5 * M_PI && angle < M_PI)
	{//upside left Q2
		yn = (((int)p_y >> sizeof(TILE_SIZE)) << sizeof(TILE_SIZE)) - 0.1;
		xn = (p_y - yn)/tan(angle) + p_x;
		ys = -TILE_SIZE;
		xs = ys / tan(angle);
		xs *= xs < 0 ? 1 : -1;

	} else if (angle > M_PI && angle < 1.5 * M_PI) {
		//3rd quarter Q3
		yn = (((int) p_y >> sizeof(TILE_SIZE))<< sizeof(TILE_SIZE)) + TILE_SIZE;
		xn =(p_y - yn)/tan(angle) + p_x;
		ys = TILE_SIZE;
		xs = ys / tan(angle);
		xs *= xs < 0 ? 1 : -1;
	}
	else {
		//4th quarter Q4
		yn = (((int) p_y >> sizeof(TILE_SIZE))<< sizeof(TILE_SIZE)) + TILE_SIZE;
		xn =(p_y - yn) / tan(angle) + p_x;
		ys = +TILE_SIZE;
		xs = ys / tan(angle);
		xs *= xs > 0 ? 1 : -1;
	}
	y_target = yn;
	x_target = xn;
	while (1)
	{
		//check boundaries
		if (x_target < 0 || y_target < 0 || y_target / TILE_SIZE >= map->height  || x_target / TILE_SIZE >= map->width)
			break;
		//check hit wall
		if(map_get_tile(map,x_target / TILE_SIZE  ,y_target / TILE_SIZE) != TILE_EMPTY && \
			!(map_get_tile(map,x_target / TILE_SIZE ,y_target / TILE_SIZE) == TILE_DOOR && map->doors_open))
		{
			player->ray.distance_h = dist(p_x,p_y,x_target, y_target);
			player->ray.hor_x = x_target;
			player->ray.hor_y = y_target;
			player->ray.hit_tile_h = map_get_tile(map, x_target / TILE_SIZE, y_target / TILE_SIZE);
			return (player->ray.distance_h);
		}
		y_target += ys;
		x_target += xs;
	}

	return(INFINITY);
}
//find vertical intersection
float v_intersection(t_map *map,t_player *player, float p_x, float p_y)
{
	float ys;
	float xs;
	float yn;
	float xn;
	double angle;
	float y_target;
	float x_target;

	angle = player->ray.ray_angle;
	if ((fabs(angle - M_PI_2) < 0.0001) || (fabs(angle - (1.5 * M_PI)) < 0.0001))
	{
		xn = p_x;
		yn = p_y;
		return (INFINITY);
	}
	else if (angle > 0 && angle <= M_PI_2)
	{// Q1
		xn = (((int) p_x >> sizeof(TILE_SIZE) ) << sizeof(TILE_SIZE)) + TILE_SIZE;
		yn = (p_x - xn) * tan(angle) + p_y;	
		xs = TILE_SIZE;
		ys = xs * tan(angle);
		ys *= ys > 0 ? -1 : 1;
	} else if (angle >= M_PI / 2 && angle < M_PI) {
		//Q2
		xn = (((int) p_x >> sizeof(TILE_SIZE)) << sizeof(TILE_SIZE)) - 0.1;
		yn = (p_x - xn) * tan(angle) + p_y;
		xs = -TILE_SIZE;
		ys = xs * tan(angle);
		ys *= ys > 0 ? -1 : 1;

	} else if (angle >= M_PI && angle < (1.5 * M_PI))
	{//Q3
		xn = (((int) p_x >> sizeof(TILE_SIZE)) << sizeof(TILE_SIZE)) - 0.1;
		yn = (p_x - xn) * tan(angle) + p_y;
		xs = -TILE_SIZE;
		ys = xs * tan(angle);
		ys *= ys < 0 ? -1 : 1;
		
	} else  {
		xn = (((int) p_x >> sizeof(TILE_SIZE) ) << sizeof(TILE_SIZE)) + TILE_SIZE;
		yn = (p_x - xn) * tan(angle) + p_y;	
		xs = TILE_SIZE;
		ys = xs * tan(angle);
		ys *= ys < 0 ? -1 : 1;

	}
	y_target = yn;
	x_target = xn;
	while (1)
	{
		//check boundaries
		if (x_target < 0 || y_target < 0 || y_target / TILE_SIZE >= map->height  || x_target / TILE_SIZE >= map->width)
			break;
		//check hit wall
		if(map_get_tile(map,x_target / TILE_SIZE ,y_target / TILE_SIZE) != TILE_EMPTY && \
			!(map_get_tile(map,x_target / TILE_SIZE ,y_target / TILE_SIZE) == TILE_DOOR && map->doors_open))
		{
			player->ray.distance_v = dist(p_x,p_y,x_target, y_target);
			player->ray.ver_x = x_target;
			player->ray.ver_y = y_target;
			player->ray.hit_tile_v = map_get_tile(map, x_target / TILE_SIZE, y_target / TILE_SIZE);
			return (player->ray.distance_v);
		}
		y_target += ys;
		x_target += xs;
	}
	return (INFINITY);
}
