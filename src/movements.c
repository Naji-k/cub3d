/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movements.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 16:20:44 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/22 16:20:44 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>
#include <math.h>

void	valid_move(t_player *player, t_map *map, float new_x, float new_y)
{
	if ((map_get_tile(map, new_x, new_y) == TILE_WALL))
		return ;
	if (!map->doors_open && (map_get_tile(map, new_x, new_y) == TILE_DOOR))
		return ;
	player->x = new_x;
	player->y = new_y;
}

void	move_player(t_player *player, t_map *map)
{
	float	pos[2];

	pos[0] = player->x;
	pos[1] = player->y;
	if (player->current_move == MOVE_FORWARD)
	{
		pos[1] += player->delta_y;
		pos[0] += player->delta_x;
	}
	else if (player->current_move == MOVE_BACKWARD)
	{
		pos[1] -= player->delta_y;
		pos[0] -= player->delta_x;
	}
	else if (player->current_move == MOVE_RIGHT)
	{
		pos[0] += player->delta_y;
		pos[1] -= player->delta_x;
	}
	else if (player->current_move == MOVE_LEFT)
	{
		pos[0] -= player->delta_y;
		pos[1] += player->delta_x;
	}
	valid_move(player, map, pos[0], pos[1]);
}

void	rotate_player(t_player *player)
{
	if (player->current_move == ROTATE_LEFT)
		player->rotation += 0.01;
	else if (player->current_move == ROTATE_RIGHT)
		player->rotation -= 0.01;
	fix_angle(&player->rotation);
	player->delta_x = cos(player->rotation) * MOVE_SPEED;
	player->delta_y = -sin(player->rotation) * MOVE_SPEED;
}
