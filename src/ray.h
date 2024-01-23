/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:18:37 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/23 12:36:03 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "map.h"

typedef struct s_player	t_player;

typedef struct s_rays
{
	float				ray_angle;
	float				distance_v;
	float				distance_h;
	float				x_target;
	float				y_target;
	float				xs;
	float				ys;
	float				end_x;
	float				end_y;
	float				ver_x;
	float				ver_y;
	float				hor_x;
	float				hor_y;
	float				line_h;
	float				line_offset;
	int					screen_h;
	int					screen_w;
	t_tile				hit_tile_h;
	t_tile				hit_tile_v;
	t_tile				hit_tile;
}						t_ray;

void	find_nearest_wall(t_player *player);
bool	is_ray_hit_wall(t_map *map, t_ray *ray);

#endif
