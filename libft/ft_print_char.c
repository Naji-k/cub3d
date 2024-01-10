/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_char.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 11:50:46 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/18 19:49:23 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

#include "ft_printers.h"

int	ft_print_char(char c, t_flags flags)
{
	int	len;

	len = 1;
	if (!flags.left_adjustment)
		len += ft_add_padding(len, flags.field_width, ' ');
	ft_putchar_fd(c, STDOUT_FILENO);
	if (flags.left_adjustment)
		len += ft_add_padding(len, flags.field_width, ' ');
	return (len);
}
