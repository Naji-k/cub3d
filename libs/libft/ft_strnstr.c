/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 14:07:21 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/04 14:40:04 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_length;
	size_t	i;

	little_length = ft_strlen(little);
	if (little_length == 0)
		return ((char *) big);
	i = 0;
	while (big[i] != '\0' && len - i >= little_length)
	{
		if (ft_strncmp(&big[i], little, little_length) == 0)
			return ((char *) &big[i]);
		i++;
	}
	return (NULL);
}
