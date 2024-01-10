/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 10:50:08 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/13 10:56:12 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

size_t	ft_strlento(const char *s, char to)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0' && s[length] != to)
		length++;
	if (s[length] == to && to != '\0')
		length++;
	return (length);
}

char	*ft_strjointo(char const *s1, char const *s2, char to)
{
	char	*new_str;
	size_t	s1_length;
	size_t	s2_length;

	s1_length = ft_strlento(s1, '\0');
	s2_length = ft_strlento(s2, to);
	new_str = malloc(s1_length + s2_length + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_length + s2_length + 1);
	ft_strlcpy(&new_str[s1_length], s2, s2_length + 1);
	return (new_str);
}

char	*ft_strdupto(const char *s, char to)
{
	char	*dest;
	size_t	size;

	size = ft_strlento(s, to) + 1;
	dest = malloc(size);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, size);
	return (dest);
}
