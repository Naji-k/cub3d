/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 11:59:21 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 23:30:10 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_length;
	size_t	s2_length;

	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	new_str = malloc(s1_length + s2_length + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_length + s2_length + 1);
	ft_strlcpy(&new_str[s1_length], s2, s2_length + 1);
	return (new_str);
}
