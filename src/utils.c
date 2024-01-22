/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 17:54:28 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/22 12:01:01 by tsteur        ########   odam.nl         */
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

/// @brief to draw a line between two points on mlx_image,
/// using a loop from 1st point,
/// to the 2nd point,
/// @param image image that will draw on it
/// @param startX X pos for the 1st point (starting point)
/// @param startY Y pos for the 1st point (starting point)
/// @param endX X pos for the 2nd point (end point)
/// @param endY Y pos for the 2nd point (end point)
/// @return
int	draw_line(mlx_image_t *image, int startX, int startY, int endX, int endY, \
				t_color color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	error2;

	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	if (startX >= (int) image->width)
		startX = (int) image->width - 1;
	if (startY >= (int) image->height)
		startY = (int) image->height - 1;
	if (endX < 0)
		endX = 0;
	if (endY < 0)
		endY = 0;
	if (startX >= (int) image->width)
		startX =(int)  image->width - 1;
	if (endY >= (int) image->height)
		endY = (int) image->height - 1;
	mlx_put_pixel(image, startX, startY, color.raw);
	dx = abs(endX - startX);
	dy = abs(endY - startY);
	sx = (startX < endX) ? 1 : -1;
	sy = (startY < endY) ? 1 : -1;
	error = dx - dy;
	while ((startX != endX || startY != endY))
	{
		mlx_put_pixel(image, startX, startY, color.raw);
		error2 = error * 2;
		if (error2 > -dy)
		{
			error -= dy;
			startX += sx;
		}
		if (error2 < dx)
		{
			error += dx;
			startY += sy;
		}
	}
	return (0);
}
