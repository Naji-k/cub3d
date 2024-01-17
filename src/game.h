/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 16:03:36 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/17 15:23:39 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <player.h>

typedef struct s_game
{
	mlx_t		*mlx;
	t_player	*player;
	t_map		*map;
}				t_game;

t_error			init_game(t_game *game, t_map *map, t_player *player);
t_error			create_map(t_game *game, size_t x, size_t y);
t_error			draw_player(t_game *game, float pos_x, float pos_y);
t_error			init_player_images(t_game *game);

void			game_loop(void *param);

int				draw_line(mlx_image_t *image, int startX, int startY, int endX,
					int endY, t_color color);
//utils
double			degree_to_rad(float deg);
float			dist(float ax, float ay, float bx, float by);
void			fix_angle(float angle);

#endif