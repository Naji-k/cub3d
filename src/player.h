/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:07:29 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/17 14:14:21 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include <map.h>
# include <ray.h>

# define TILE_SIZE 32
#define MOVE_SPEED 0.1

typedef enum e_move_direction
{
	NONE = 0,
	ROTATE_LEFT,
	ROTATE_RIGHT,
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT
}						t_move_direction;

typedef struct s_player
{
	mlx_image_t			*player_image;
	mlx_image_t			*player_lines;
	mlx_image_t			*wall;
	float				x;
	float				y;
	float				fov;
	float				rotation;
	float				delta_x;
	float				delta_y;
	int					size;
	t_ray				ray;
	t_move_direction	current_move;
}						t_player;

void			draw_pixels(mlx_image_t *img, uint32_t color, size_t size);
t_error			ray_casting(t_map *map, t_player *player);

float			h_intersection(t_map *map, t_player *player, float p_x,
					float p_y);
float			v_intersection(t_map *map, t_player *player, float p_x,
					float p_y);

#endif