/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_uint.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 11:49:35 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/18 19:55:59 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

#include "ft_printers.h"

static int	count_digits(unsigned int n)
{
	int	digits;

	n /= 10;
	digits = 1;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static void	write_uint_to_string(unsigned int n, char *str)
{
	unsigned int	modulo;
	unsigned int	div;

	modulo = n % 10;
	div = n / 10;
	if (div != 0)
		write_uint_to_string(div, str);
	str[ft_strlen(str)] = '0' + modulo;
}

static char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		digits;

	digits = count_digits(n);
	str = malloc(digits + 1);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, digits + 1);
	write_uint_to_string(n, str);
	str[digits] = '\0';
	return (str);
}

int	ft_print_uint(unsigned int n, t_flags flags)
{
	int		len;
	char	*str;

	str = ft_uitoa(n);
	if (str == NULL)
		return (-1);
	len = ft_strlen(str);
	if (flags.precision == 0 && n == 0)
		len = 0;
	if (!flags.left_adjustment && !flags.zero_padded)
		len += ft_add_padding(len, flags.field_width, ' ');
	if (flags.zero_padded && !flags.left_adjustment && flags.precision < 0)
		len += ft_add_padding(len, flags.field_width, '0');
	else if (flags.precision >= 0 && !flags.left_adjustment)
		len += ft_add_padding(len, flags.precision, '0');
	if (flags.precision != 0 || n != 0)
		ft_putstr_fd(str, STDOUT_FILENO);
	if (flags.left_adjustment)
		len += ft_add_padding(len, flags.field_width, ' ');
	free(str);
	return (len);
}
