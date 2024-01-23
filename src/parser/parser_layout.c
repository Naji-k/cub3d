/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_layout.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 13:16:56 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/23 15:55:37 by tsteur        ########   odam.nl         */
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

static t_error	read_map_lines(int file, t_list **lines, size_t *longest)
{
	char	*current_line;
	t_list	*current_node;

	*lines = NULL;
	while (true)
	{
		current_line = get_next_line(file);
		if (current_line == NULL)
			break ;
		if (current_line[0] != '\n')
			break ;
		free(current_line);
	}
	while (current_line != NULL)
	{
		current_node = ft_lstnew(current_line);
		if (current_node == NULL)
			return (ft_lstclear(lines, free), ERR_MALLOC);
		ft_lstadd_back(lines, current_node);
		if (ft_strlen(current_line) - 1 > *longest)
			*longest = ft_strlen(current_line) - 1;
		current_line = get_next_line(file);
	}
	return (OK);
}

static t_error	read_player(t_player *player, char c, unsigned long pos[2])
{
	if (! isnan(player->x))
		return (ERR_DUPLICATE_PLAYER);
	player->x = pos[0];
	player->y = pos[1];
	if (c == 'E')
		player->rotation = 0.0 * M_PI;
	else if (c == 'N')
		player->rotation = 0.5 * M_PI;
	else if (c == 'W')
		player->rotation = 1.0 * M_PI;
	else if (c == 'S')
		player->rotation = 1.5 * M_PI;
	return (OK);
}

static t_error	read_tile(t_map *map, t_player *player, char c, \
							unsigned long pos[2])
{
	if (c == ' ')
		map_set_tile(map, pos[0], pos[1], TILE_NONE);
	else if (c == '0')
		map_set_tile(map, pos[0], pos[1], TILE_EMPTY);
	else if (c == '1')
		map_set_tile(map, pos[0], pos[1], TILE_WALL);
	else if (c == '2')
	{
		map_set_tile(map, pos[0], pos[1], TILE_DOOR);
		if (map->door1_texture == NULL || map->door2_texture == NULL || \
			map->door3_texture == NULL)
			return (ERR_MISSING_DOOR_TEXTURES);
	}
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		map_set_tile(map, pos[0], pos[1], TILE_EMPTY);
		return (read_player(player, c, pos));
	}
	else
		return (ERR_INVALID_IDENTIFIER);
	return (OK);
}

static t_error	fill_map(t_map *map, t_player *player, t_list *lines)
{
	t_error			err;
	char			*current_line;
	unsigned long	x;
	unsigned long	y;

	player->x = NAN;
	y = 0;
	while (lines != NULL)
	{
		x = 0;
		current_line = lines->content;
		while (current_line[x] != '\0' && current_line[x] != '\n')
		{
			err = read_tile(map, player, current_line[x], \
							(unsigned long [2]){x, y});
			if (err != OK)
				return (err);
			x++;
		}
		lines = lines->next;
		y++;
	}
	if (isnanf(player->x))
		return (ERR_NO_PLAYER);
	return (OK);
}

t_error	parse_layout(int file, t_map *map, t_player *player)
{
	t_error			err;
	t_list			*lines;

	err = read_map_lines(file, &lines, &map->width);
	if (err != OK)
		return (err);
	map->height = ft_lstsize(lines);
	map->tiles = ft_calloc(sizeof(t_tile), map->width * map->height);
	if (map->tiles == NULL)
		return (ft_lstclear(&lines, free), ERR_MALLOC);
	err = fill_map(map, player, lines);
	ft_lstclear(&lines, free);
	return (err);
}
