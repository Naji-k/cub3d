/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/10 16:43:06 by tsteur        #+#    #+#                 */
/*   Updated: 2024/01/10 16:45:13 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

typedef union u_color
{
	int	raw;
	struct 
	{
		int8_t	r;
		int8_t	g;
		int8_t	b;
		int8_t	a;
	};
}	t_color;


#endif