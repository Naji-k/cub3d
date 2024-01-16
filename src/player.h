/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:07:29 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/11 12:10:07 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

#include <ray.h>
#include <map.h>

#define TILE_SIZE 32


typedef struct s_player
{
	mlx_image_t	*player_image;
	mlx_image_t	*player_lines;
	mlx_image_t	*wall;
	float	x;
	float	y;
	float	fov;
	float	rotation;
	float	delta_x;
	float	delta_y;
	int		size;
	t_ray	ray;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_player	*player;
	t_map		*map;
}				t_game;

t_error init_game(t_game *game, t_map *map, t_player *player);
t_error create_map(t_game *game, size_t x, size_t y);
t_error draw_player(t_game *game, float pos_x, float pos_y);
void	draw_pixels(mlx_image_t *img, uint32_t color, size_t size);
t_error find_intersection(t_game *game);

#endif