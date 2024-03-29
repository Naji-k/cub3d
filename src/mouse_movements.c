/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_movements.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 12:43:22 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/23 16:30:25 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "game.h"

void	cursor_moves(double xpos, double ypos, void *param)
{
	t_game		*game;
	t_player	*player;
	
	
	game = param;
	player = game->player;
	if (player->prev_xpos < 0)
		player->prev_xpos = xpos;
	else if (fabs(player->prev_xpos - xpos) < 8)
		return ;
	else
	{
		if (xpos > player->prev_xpos)
			player->current_move = ROTATE_RIGHT;
		else if (xpos < player->prev_xpos)
			player->current_move = ROTATE_LEFT;
	}
	player->prev_xpos = xpos;
	rotate_player(player);
	(void)ypos;
	player->current_move = NONE;
	update(game);
}
