/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_string.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 11:32:05 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/18 19:43:46 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

#include "ft_printers.h"

int	ft_print_string(char *str, t_flags flags)
{
	int	len;

	if (str == NULL)
		return (ft_print_string("(null)", flags));
	len = ft_strlen(str);
	if (!(flags.precision < 0 || (int) ft_strlen(str) < flags.precision))
		len = flags.precision;
	if (!flags.left_adjustment)
		len += ft_add_padding(len, flags.field_width, ' ');
	if (flags.precision < 0 || (int) ft_strlen(str) < flags.precision)
		ft_putstr_fd(str, STDOUT_FILENO);
	else
		write(STDOUT_FILENO, str, flags.precision);
	if (flags.left_adjustment)
		len += ft_add_padding(len, flags.field_width, ' ');
	return (len);
}
