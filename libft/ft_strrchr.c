/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 12:52:27 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/03 14:44:28 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;
	size_t	i;

	last_occurrence = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			last_occurrence = (char *) &s[i];
		i++;
	}
	if (c == '\0')
		return ((char *) &s[i]);
	return (last_occurrence);
}
