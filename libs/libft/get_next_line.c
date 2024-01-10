/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 10:51:03 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/15 17:24:49 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

#include "libft.h"

#include "get_next_line_utils.h"

static int	handle_overflow(char **overflow, char **line)
{
	char	*tmp;

	if (*overflow == NULL || ft_strlento(*overflow, '\0') == 0)
	{
		if (*overflow)
			free(*overflow);
		*overflow = NULL;
		return (0);
	}
	if (ft_strchr(*overflow, '\n'))
	{
		*line = ft_strdupto(*overflow, '\n');
		if (*line == NULL)
			return (1);
		tmp = *overflow;
		*overflow = ft_strdupto(ft_strchr(*overflow, '\n') + 1, '\0');
		free(tmp);
		return (0);
	}
	*line = ft_strdupto(*overflow, '\0');
	if (*line == NULL)
		return (1);
	free(*overflow);
	*overflow = NULL;
	return (0);
}

static ssize_t	clear_and_read(int fd, char *buffer)
{
	ft_bzero(buffer, BUFFER_SIZE + 1);
	return (read(fd, buffer, BUFFER_SIZE));
}

static ssize_t	read_next(char **overflow, char **line, char *buffer, int fd)
{
	char		*tmp;
	ssize_t		bytes_read;

	bytes_read = clear_and_read(fd, buffer);
	while (bytes_read > 0)
	{
		tmp = *line;
		if (*line == NULL)
			*line = ft_strdupto(buffer, '\n');
		else
			*line = ft_strjointo(*line, buffer, '\n');
		if (tmp)
			free(tmp);
		if (*line == NULL)
			return (-1);
		if (ft_strchr(buffer, '\n'))
		{
			*overflow = ft_strdupto(ft_strchr(buffer, '\n') + 1, '\0');
			if (*overflow == NULL)
				return (-1);
			break ;
		}
		bytes_read = clear_and_read(fd, buffer);
	}
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*overflow[FD_MAX] = {NULL};
	char		*line;
	char		*buffer;
	ssize_t		last_bytes_read;

	if (fd >= FD_MAX)
		return (NULL);
	line = NULL;
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	if (handle_overflow(&overflow[fd], &line) == 1)
		return (free(buffer), NULL);
	if (line != NULL && ft_strchr(line, '\n'))
		return (free(buffer), line);
	last_bytes_read = read_next(&overflow[fd], &line, buffer, fd);
	free(buffer);
	if (last_bytes_read == -1)
	{
		if (line != NULL)
			free(line);
		return (NULL);
	}
	return (line);
}
