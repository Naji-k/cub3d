/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tycho <tycho@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 12:27:27 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 23:26:02 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_length;
	size_t	start_trim;
	size_t	end_trim;

	s1_length = ft_strlen(s1);
	start_trim = 0;
	end_trim = 0;
	while (ft_strchr(set, s1[start_trim]))
		start_trim++;
	while (ft_strchr(set, s1[s1_length - end_trim - 1]))
		end_trim++;
	return (ft_substr(s1, start_trim, ft_strlen(s1) - start_trim - end_trim));
}
