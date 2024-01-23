/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 16:03:36 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/23 13:32:25 by tsteur        ########   odam.nl         */
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
	t_map		map_noptr;
	t_player	player_noptr;
}				t_game;

t_error	init_game(t_game *game);
t_error	create_map(t_game *game);
t_error	draw_player(t_game *game);
t_error	init_player_images(t_game *game);

void	update(t_game *game);

void	draw_line(mlx_image_t *image, int start[2], int end[2], t_color color);
//utils
double	degree_to_rad(float deg);
float	dist(float ax, float ay, float bx, float by);
void	fix_angle(float *angle);
void	key_hook(mlx_key_data_t key, void *param);
void	loop_hook(void *param);

#endif