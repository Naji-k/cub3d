/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:13:00 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/11 16:26:56 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
	(void) file;
	(void) map;
	(void) player;
	return (OK);
}

t_error	parse_file(const char *file_path, t_map *map, t_player *player)
{
	t_error	err;
	int		file;

	file = open(file_path, O_RDONLY);
	if (file == -1)
		return (ERR_OPEN);
	err = parse_textures_and_colors(file, map);
	if (err != OK)
	{
		//free map
		close(file);
		return (err);
	}
	err = parse_layout(file, map, player);
	if (err != OK)
	{
		//free map
		close(file);
		return (err);
	}
	close(file);
	return (OK);
}
