/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tycho <tycho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 14:57:50 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/10 19:18:01 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	malloc_size;

	malloc_size = nmemb * size;
	if (nmemb != 0 && malloc_size / nmemb != size)
		return (NULL);
	ptr = malloc(malloc_size);
	if (ptr != NULL)
		ft_bzero(ptr, malloc_size);
	return (ptr);
}
