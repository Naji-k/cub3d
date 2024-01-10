/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 12:05:34 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/03 14:43:56 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islower(int c)
{
	return ((unsigned char) c >= 'a' && (unsigned char) c <= 'z');
}

int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 32);
	return (c);
}
