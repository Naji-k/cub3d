/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_int.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 11:43:09 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/18 20:34:09 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

#include "ft_printers.h"

static void	print_sign(int n, t_flags flags)
{
	if (n >= 0 && flags.plus_before_pos)
		ft_putchar_fd('+', STDOUT_FILENO);
	else if (n >= 0 && flags.space_before_pos)
		ft_putchar_fd(' ', STDOUT_FILENO);
	if (n < 0)
		ft_putchar_fd('-', STDOUT_FILENO);
}

int	ft_print_int(int n, t_flags flags)
{
	int		len;
	char	*str;

	str = ft_itoa(n);
	if (str == NULL)
		return (-1);
	len = ft_strlen(str);
	len += n >= 0 && (flags.plus_before_pos || flags.space_before_pos);
	len *= !(flags.precision == 0 && n == 0);
	if (!flags.left_adjustment && !flags.zero_padded)
		len += ft_add_padding(len, flags.field_width, ' ');
	print_sign(n, flags);
	if (flags.zero_padded && !flags.left_adjustment && flags.precision < 0)
		len += ft_add_padding(len, flags.field_width, '0');
	else if (flags.precision >= 0 && !flags.left_adjustment)
		len += ft_add_padding(len, flags.precision + (n < 0), '0');
	if (flags.precision != 0 || n != 0)
		ft_putstr_fd(str + (n < 0), STDOUT_FILENO);
	if (flags.left_adjustment)
		len += ft_add_padding(len, flags.field_width, ' ');
	return (free(str), len);
}
