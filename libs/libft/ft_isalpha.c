/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 13:24:44 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/02 14:33:13 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islower(int c)
{
	return ((unsigned char) c >= 'a' && (unsigned char) c <= 'z');
}

static int	ft_isupper(int c)
{
	return ((unsigned char) c >= 'A' && (unsigned char) c <= 'Z');
}

int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
