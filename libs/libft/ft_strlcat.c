/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 11:50:52 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 11:46:09 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_length;
	size_t	i;

	dst_length = ft_strlen(dst);
	i = 0;
	if (size <= dst_length)
		dst_length = size;
	else if (size != 0)
	{
		while (src[i] != '\0' && dst_length + i < size - 1)
		{
			dst[dst_length + i] = src[i];
			i++;
		}
		dst[dst_length + i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (dst_length + i);
}
