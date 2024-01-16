/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 13:07:04 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/16 13:25:41 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

#include "errors.h"

static const char const	*g_error_strings[] = {
[OK] = "",
[ERR_MALLOC] = "out of memory",
[ERR_OPEN] = "failed to open file",
[ERR_READ] = "failed to read from file",
[ERR_MLX] = "",
	// color
[ERR_COLOR_VALUE_OUT_OF_RANGE] = "supplied color has an out of range value",
[ERR_COLOR_TOO_MANY_VALUES] = "supplied color has to many values",
[ERR_COLOR_TOO_LITTLE_VALUES] = "supplied color has to little values",
	// parsing
[ERR_INVALID_EXTENSION] = "supplied file has an invalid extention",
[ERR_MISSING_TEXTURE] = "a texture is missing",
[ERR_DUPLICATE_TEXTURE] = "a texture was found twice",
[ERR_MISSING_COLOR] = "a color is missing",
[ERR_DUPLICATE_COLOR] = "a color was found twice",
[ERR_INVALID_IDENTIFIER] = "an invalid identifier was found",
[ERR_DUPLICATE_PLAYER] = "a player was found twice",
[ERR_NO_PLAYER] = "no player was found",
};

const char	*error_string(t_error err)
{
	if (err == ERR_MLX)
		return (mlx_strerror(mlx_errno));
	return (g_error_strings[err]);
}
