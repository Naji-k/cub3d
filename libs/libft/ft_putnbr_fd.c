/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:42:04 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 23:30:45 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	modulo;
	int	div;

	modulo = n % 10;
	div = n / 10;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		modulo = -modulo;
		div = -div;
	}
	if (div != 0)
		ft_putnbr_fd(div, fd);
	ft_putchar_fd('0' + modulo, fd);
}
