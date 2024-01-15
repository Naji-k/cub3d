/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:10:18 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/15 13:17:35 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "errors.h"
# include "map.h"
# include "player.h"

t_error	parse_file(const char *file_path, t_map *map, t_player *player);
t_error	parse_layout(int file, t_map *map, t_player *player);

#endif