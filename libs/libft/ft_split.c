/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 13:40:18 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/12 09:42:28 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static size_t	count_splits(const char *s, char c)
{
	size_t	split_count;
	int		last_was_split;
	size_t	i;

	split_count = 0;
	last_was_split = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if (last_was_split && s[i] != c)
		{
			split_count++;
			last_was_split = 0;
		}
		if (s[i] == c)
			last_was_split = 1;
		i++;
	}
	return (split_count);
}

static size_t	get_next_split_length(const char *s, char c)
{
	size_t	length;

	length = 0;
	while (s[length] != c && s[length] != '\0')
		length++;
	return (length);
}

static char	**free_array(char **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	index;
	size_t	i;
	size_t	split_length;

	strs = ft_calloc(count_splits(s, c) + 1, sizeof(char *));
	if (strs == NULL)
		return (NULL);
	index = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			split_length = get_next_split_length(&s[i], c);
			strs[index] = ft_substr(s, i, split_length);
			if (strs[index] == NULL)
				return (free_array(strs, index));
			index++;
			i += split_length;
		}
		else
			i++;
	}
	return (strs);
}
