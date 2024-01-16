/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nakanoun <nakanoun@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:18:37 by nakanoun      #+#    #+#                 */
/*   Updated: 2024/01/15 14:18:37 by nakanoun      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_Y
# define RAY_Y

typedef struct s_rays
{
	double	ray_angle;
	float	distance_v;
	float	distance_h;
	float	x_target;
	float	y_target;
	float	xs;
	float	ys;
	int		ver_x;
	int		ver_y;
	int		hor_x;
	int		hor_y;
	float	lineH;
	float	lineO;
	int		screenH;
	int		screenW;
}			t_ray;

#endif
