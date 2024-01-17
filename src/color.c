/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 14:29:54 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/17 15:33:11 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "libft.h"

#include "errors.h"

#include "color.h"

t_error	asci_to_color_rgb(t_color *color, char *string)
{
	int	value;
	int	i;

	i = 0;
	while (i < 3)
	{
		value = ft_atoi(string);
		if (value < 0 || value > 255)
			return (ERR_COLOR_VALUE_OUT_OF_RANGE);
		color->indexable[i] = (uint8_t) value;
		while (*string != ',')
		{
			if (*string == '\0')
			{
				if (i < 2)
					return (ERR_COLOR_TOO_LITTLE_VALUES);
				color->a = 255;
				return (OK);
			}
			string++;
		}
		string++;
		i++;
	}
	return (ERR_COLOR_TOO_MANY_VALUES);
}
