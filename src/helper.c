/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helper.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/19 17:15:58 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/19 17:15:58 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <game.h>
#include <math.h>
#include <stdio.h>

int can_move_to(t_player *player, t_map* map, float newX, float newY) {


	if (player->direction == NORTH)
	{
		printf("N\n");
		if(map_get_tile(map, newX -0.1, newY - 0.1) != TILE_WALL)
			return (0);
	} else if (player->direction == SOUTH)
	{
		printf("S\n");
		if((map_get_tile(map, newX +0.1, newY + 0.1) != TILE_WALL))
			return (0);
	} else if (player->direction == EAST) {
		printf("E\n");
		if((map_get_tile(map, newX + 0.1, newY +0.1 ) != TILE_WALL))
			return (0);
	}else {
		if((map_get_tile(map, newX - 0.1, newY-0.1) != TILE_WALL))
		{
			printf("W\n");
			return(0);
		}
	}
    return 1;
}

t_player_direction get_player_direction(double angle) 
{
    if (angle >= M_PI / 4 && angle < 3 * M_PI / 4) {
        return NORTH;
    } else if (angle >= 3 * M_PI / 4 && angle < 5 * M_PI / 4) {
        return WEST;
    } else if (angle >= 5 * M_PI / 4 && angle < 7 * M_PI / 4) {
        return SOUTH;
    } else {
        return EAST; 
    }
}