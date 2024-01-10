/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 19:36:37 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/18 19:57:26 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

int	ft_add_padding(int output_length, int field_with, char padding_char)
{
	int	i;

	i = 0;
	while (i < field_with - output_length)
	{
		ft_putchar_fd(padding_char, STDOUT_FILENO);
		i++;
	}
	return (i);
}
