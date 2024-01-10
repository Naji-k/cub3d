/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 12:31:17 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/03 14:44:04 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isupper(int c)
{
	return ((unsigned char) c >= 'A' && (unsigned char) c <= 'Z');
}

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c + 32);
	return (c);
}
