/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 17:54:28 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/23 13:35:37 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>
#include <math.h>
#include <stdlib.h>

double	degree_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

// find the distance between two points
float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt(((ax - bx) * (ax - bx)) + ((ay - by) * (ay - by))));
}

/// @brief fix angle value should not be < 0 && ! >= 360
/// @param angle
void	fix_angle(float *angle)
{
	if (*angle >= 2 * M_PI)
	{
		*angle -= 2 * M_PI;
		fix_angle(angle);
	}
	else if (*angle < 0)
	{
		*angle += (2 * M_PI);
		fix_angle(angle);
	}
}

void	clamp_bounds(mlx_image_t *image, int start[2], int end[2])
{
	if (start[0] < 0)
		start[0] = 0;
	if (start[1] < 0)
		start[1] = 0;
	if (start[0] >= (int) image->width)
		start[0] = (int) image->width - 1;
	if (start[1] >= (int) image->height)
		start[1] = (int) image->height - 1;
	if (end[0] < 0)
		end[0] = 0;
	if (end[1] < 0)
		end[1] = 0;
	if (start[0] >= (int) image->width)
		start[0] = (int) image->width - 1;
	if (end[1] >= (int) image->height)
		end[1] = (int) image->height - 1;
}

/// @brief to draw a line between two points on mlx_image,
/// using a loop from 1st point,
/// to the 2nd point,
/// @param image image that will draw on it
/// @param startX X pos for the 1st point (starting point)
/// @param startY Y pos for the 1st point (starting point)
/// @param endX X pos for the 2nd point (end point)
/// @param endY Y pos for the 2nd point (end point)
void	draw_line(mlx_image_t *image, int start[2], int end[2], t_color color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	error2;

	clamp_bounds(image, start, end);
	mlx_put_pixel(image, start[0], start[1], color.raw);
	dx = abs(end[0] - start[0]);
	dy = abs(end[1] - start[1]);
	sx = -1;
	if (start[0] < end[0])
		sx = 1;
	sy = -1;
	if (start[1] < end[1])
		sy = 1;
	error = dx - dy;
	while ((start[0] != end[0] || start[1] != end[1]))
	{
		mlx_put_pixel(image, start[0], start[1], color.raw);
		error2 = error * 2;
		if (error2 > -dy)
		{
			error -= dy;
			start[0] += sx;
		}
		if (error2 < dx)
		{
			error += dx;
			start[1] += sy;
		}
	}
}
