/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 10:50:18 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/30 09:55:19 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H

# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# ifndef FD_MAX
#  define FD_MAX 2048
# endif

size_t	ft_strlento(const char *s, char to);
char	*ft_strjointo(char const *s1, char const *s2, char to);
char	*ft_strdupto(const char *s, char to);

#endif