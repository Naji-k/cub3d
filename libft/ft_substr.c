/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tycho <tycho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 11:05:45 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 23:24:12 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	sub_str_size;
	size_t	s_length;

	s_length = ft_strlen(s);
	sub_str_size = min(s_length - start, len) + 1;
	if (start > s_length)
		sub_str_size = 1;
	sub_str = malloc(sub_str_size);
	if (sub_str == NULL)
		return (NULL);
	if (start > s_length)
		sub_str[0] = '\0';
	else
		ft_strlcpy(sub_str, &s[start], sub_str_size);
	return (sub_str);
}
