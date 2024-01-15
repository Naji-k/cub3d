/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_layout.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 13:16:56 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/15 13:17:19 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define __USE_MISC 1
#include <math.h>

#include "MLX42.h"

#include "libft.h"

#include "errors.h"
#include "color.h"
#include "map.h"
#include "player.h"

#include "parser.h"

t_error	parse_layout(int file, t_map *map, t_player *player)
{
	char			*current_line;
	t_list			*lines;
	t_list			*current_node;
	unsigned long	x;
	unsigned long	y;

	while (true)
	{
		current_line = get_next_line(file);
		if (current_line == NULL)
			break ;
		if (current_line[0] != '\n')
			break ;
		free (current_line);
	}
	while (current_line != NULL)
	{
		current_node = ft_lstnew(current_line);
		if (current_node == NULL)
			return (ft_lstclear(&lines, free), ERR_MALLOC);
		ft_lstadd_back(&lines, current_node);
		current_line = get_next_line(file);
	}
	current_node = lines;
	while (current_node != NULL)
	{
		if (ft_strlen(current_node->content) - 1 > map->width)
			map->width = ft_strlen(current_node->content) - 1;
		current_node = current_node->next;
	}
	map->height = ft_lstsize(lines);
	map->tiles = ft_calloc(sizeof(t_tile), map->width * map->height);
	if (map->tiles == NULL)
		return (ft_lstclear(&lines, free), ERR_MALLOC);
	y = 0;
	current_node = lines;
	player->x = NAN;
	while (current_node != NULL)
	{
		x = 0;
		current_line = current_node->content;
		while (current_line[x] != '\0' && current_line[x] != '\n')
		{
			if (current_line[x] == '0' || current_line[x] == ' ')
				map_set_tile(map, x, y, TILE_EMPTY);
			else if (current_line[x] == '1')
				map_set_tile(map, x, y, TILE_WALL);
			else if (current_line[x] == '2')
				map_set_tile(map, x, y, TILE_DOOR);
			else if (current_line[x] == 'N' || current_line[x] == 'E' || \
					current_line[x] == 'S' || current_line[x] == 'W')
			{
				if (! isnan(player->x))
					return (ft_lstclear(&lines, free), ERR_DUPLICATE_PLAYER);
				map_set_tile(map, x, y, TILE_EMPTY);
				player->x = x;
				player->y = y;
				if (current_line[x] == 'N')
					player->rotation = 0.0 * M_PI;
				else if (current_line[x] == 'E')
					player->rotation = 0.5 * M_PI;
				else if (current_line[x] == 'S')
					player->rotation = 1.0 * M_PI;
				else if (current_line[x] == 'W')
					player->rotation = 1.5 * M_PI;
			}
			else
				return (ft_lstclear(&lines, free), ERR_INVALID_IDENTIFIER);
			x++;
		}
		current_node = current_node->next;
		y++;
	}
	ft_lstclear(&lines, free);
	if (player->x == NAN)
		return (ERR_NO_PLAYER);
	return (OK);
}