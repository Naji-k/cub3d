/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:43:06 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/19 15:09:45 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

# include "errors.h"

typedef union u_color
{
	int32_t	raw;
	uint8_t	indexable[4];
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t g;
		uint8_t	r;
	};
}	t_color;

t_error	asci_to_color_rgb(t_color *color, char *string);

#endif