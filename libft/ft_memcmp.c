/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 13:58:26 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/03 14:42:54 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((char *) s1)[i] == ((char *) s2)[i] && i < n)
		i++;
	if (i >= n)
		return (0);
	return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}
