/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:05:13 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/03 15:15:43 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	size;

	size = ft_strlen(s) + 1;
	dest = malloc(size);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, size);
	return (dest);
}
