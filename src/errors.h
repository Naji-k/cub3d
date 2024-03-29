/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:49:48 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/19 13:18:40 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum e_error
{
	// global
	OK = 0,
	ERR_MALLOC,
	ERR_OPEN,
	ERR_READ,
	ERR_MLX,
	// color
	ERR_COLOR_VALUE_OUT_OF_RANGE,
	ERR_COLOR_TOO_MANY_VALUES,
	ERR_COLOR_TOO_LITTLE_VALUES,
	// parsing
	ERR_INVALID_EXTENSION,
	ERR_MISSING_TEXTURE,
	ERR_DUPLICATE_TEXTURE,
	ERR_MISSING_COLOR,
	ERR_DUPLICATE_COLOR,
	ERR_INVALID_IDENTIFIER,
	ERR_DUPLICATE_PLAYER,
	ERR_NO_PLAYER,
	ERR_MISSING_DOOR_TEXTURES,
}	t_error;

const char	*error_string(t_error err);

#endif