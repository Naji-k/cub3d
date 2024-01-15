/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:13:00 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/15 13:05:42 by tsteur        ########   odam.nl         */
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

#define FLOOR_COLOR_FIELD 1
#define CEILING_COLOR_FIELD 2
#define COLOR_FIELDS 3

static t_error	string_to_texture(char *string, mlx_texture_t **texture)
{
	while (*string == ' ')
		string++;
	if (*texture != NULL)
		return (ERR_DUPLICATE_TEXTURE);
	*texture = mlx_load_png(string);
	if (*texture == NULL)
		return (ERR_MLX);
	return (OK);
}

static t_error	parse_line(char *current_line, t_map *map, int *found_fields)
{
	if (current_line[0] == '\0')
		return (OK);
	if (!ft_strncmp("NO ", current_line, 3))
		return (string_to_texture(current_line + 3, &map->north_texture));
	if (!ft_strncmp("EA ", current_line, 3))
		return (string_to_texture(current_line + 3, &map->east_texture));
	if (!ft_strncmp("SO ", current_line, 3))
		return (string_to_texture(current_line + 3, &map->south_texture));
	if (!ft_strncmp("WE ", current_line, 3))
		return (string_to_texture(current_line + 3, &map->west_texture));
	if (!ft_strncmp("F ", current_line, 2))
	{
		if (*found_fields & FLOOR_COLOR_FIELD)
			return (ERR_DUPLICATE_COLOR);
		*found_fields |= FLOOR_COLOR_FIELD;
		return (asci_to_color_rgb(&map->floor_color, current_line + 2));
	}
	if (!ft_strncmp("C ", current_line, 2))
	{
		if (*found_fields & CEILING_COLOR_FIELD)
			return (ERR_DUPLICATE_COLOR);
		*found_fields |= CEILING_COLOR_FIELD;
		return (asci_to_color_rgb(&map->ceiling_color, current_line + 2));
	}
	return (ERR_INVALID_IDENTIFIER);
}

t_error	parse_textures_and_colors(int file, t_map *map)
{
	t_error	err;
	char	*current_line;
	int		found_fields;

	ft_bzero(map, sizeof(t_map));
	found_fields = 0;
	while (true)
	{
		current_line = get_next_line(file);
		if (current_line == NULL)
			break ;
		if (ft_strchr(current_line, '\n'))
			current_line[ft_strlen(current_line) - 1] = '\0';
		err = parse_line(current_line, map, &found_fields);
		free(current_line);
		if (err != OK)
			return (err);
		if ((found_fields ^ COLOR_FIELDS) == 0 && \
				map->north_texture != NULL && map->east_texture != NULL && \
				map->south_texture != NULL && map->west_texture != NULL)
			return (OK);
	}
	if (((found_fields & COLOR_FIELDS) ^ COLOR_FIELDS) != 0)
		return (ERR_MISSING_COLOR);
	return (ERR_MISSING_TEXTURE);
}

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

t_error	parse_file(const char *file_path, t_map *map, t_player *player)
{
	t_error	err;
	int		file;

	file = open(file_path, O_RDONLY);
	if (file == -1)
		return (ERR_OPEN);
	if (read(file, NULL, 0) == -1)
		return (close(file), ERR_READ);
	err = parse_textures_and_colors(file, map);
	if (err != OK)
	{
		map_destruct(map);
		close(file);
		return (err);
	}
	err = parse_layout(file, map, player);
	close(file);
	if (err != OK)
	{
		map_destruct(map);
		return (err);
	}
	return (OK);
}
