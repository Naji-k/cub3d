/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_hex.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 12:03:22 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/18 20:33:37 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

#include "ft_printers.h"

#define HEXCHARSET "0123456789abcdef"

static int	count_digits(unsigned long n)
{
	int	digits;

	n /= 16;
	digits = 1;
	while (n != 0)
	{
		n /= 16;
		digits++;
	}
	return (digits);
}

static void	write_long_to_hexstring(unsigned long n, char *str, int uppercase)
{
	unsigned long	modulo;
	unsigned long	div;

	modulo = n % 16;
	div = n / 16;
	if (div != 0)
		write_long_to_hexstring(div, str, uppercase);
	if (uppercase)
		str[ft_strlen(str)] = ft_toupper(HEXCHARSET[modulo]);
	else
		str[ft_strlen(str)] = HEXCHARSET[modulo];
}

static char	*ft_ultohex(unsigned long n, int uppercase)
{
	char	*str;
	int		digits;

	digits = count_digits(n);
	str = malloc(digits + 1);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, digits + 1);
	write_long_to_hexstring(n, str, uppercase);
	str[digits] = '\0';
	return (str);
}

static void	add_prefix(int uppercase)
{
	if (uppercase)
		ft_putstr_fd("0X", STDOUT_FILENO);
	else
		ft_putstr_fd("0x", STDOUT_FILENO);
}

int	ft_print_hex(unsigned long n, int uppercase, int is_pointer, t_flags flags)
{
	int		len;
	char	*str;

	if (is_pointer && n == 0)
		return (ft_print_string("(nil)", flags));
	str = ft_ultohex(n, uppercase);
	if (str == NULL)
		return (-1);
	len = ft_strlen(str);
	len += (is_pointer || (flags.alternate && n != 0)) * 2;
	len *= !(flags.precision == 0 && n == 0);
	if (!flags.left_adjustment && !flags.zero_padded)
		len += ft_add_padding(len, flags.field_width, ' ');
	if (is_pointer || (flags.alternate && n != 0))
		add_prefix(uppercase);
	if (flags.zero_padded && !flags.left_adjustment && flags.precision < 0)
		len += ft_add_padding(len, flags.field_width, '0');
	else if (flags.precision >= 0 && !flags.left_adjustment)
		len += ft_add_padding(len, flags.precision, '0');
	if (flags.precision != 0 || n != 0)
		ft_putstr_fd(str, STDOUT_FILENO);
	if (flags.left_adjustment)
		len += ft_add_padding(len, flags.field_width, ' ');
	return (free(str), len);
}
