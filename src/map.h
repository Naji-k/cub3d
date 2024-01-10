/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:34:23 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/10 16:46:02 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "color.h"

typedef enum e_tile
{
	EMPTY = 0,
	WALL,
	DOOR
}	t_tile;

typedef struct s_map
{
	// images
	t_color	floor_color;
	t_color	ceiling_color;
	e_tile	**tiles;
}	t_map;

#endif