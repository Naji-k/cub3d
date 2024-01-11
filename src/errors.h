/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:49:48 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/11 15:56:53 by tsteur        ########   odam.nl         */
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
	ERR_MLX,
	// color
	ERR_COLOR_VALUE_OUT_OF_RANGE,
	ERR_COLOR_TOO_MANY_VALUES,
	ERR_COLOR_TOO_LITTLE_VALUES,
	// parsing
	ERR_MISSING_TEXTURE,
	ERR_DUPLICATE_TEXTURE,
	ERR_MISSING_COLOR,
	ERR_DUPLICATE_COLOR,
	ERR_INVALID_IDENTIFIER
}	t_error;

#endif