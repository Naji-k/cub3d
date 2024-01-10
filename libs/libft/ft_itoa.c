/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 15:51:10 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 23:24:47 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static int	count_digits(int n)
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

static void	write_int_to_string(int n, char *str)
{
	int	modulo;
	int	div;

	modulo = n % 10;
	div = n / 10;
	if (n < 0)
	{
		modulo = -modulo;
		div = -div;
	}
	if (div != 0)
		write_int_to_string(div, str);
	str[ft_strlen(str)] = '0' + modulo;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digits;
	int		is_negative;

	digits = count_digits(n);
	is_negative = n < 0;
	str = malloc(digits + is_negative + 1);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, digits + is_negative + 1);
	if (is_negative)
		str[0] = '-';
	write_int_to_string(n, str);
	str[digits + is_negative] = '\0';
	return (str);
}
