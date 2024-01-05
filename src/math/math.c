/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:57 by slampine          #+#    #+#             */
/*   Updated: 2024/01/05 15:26:29 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	within_360(double degree)
{
	while (degree < 0)
		degree += 360;
	while (degree >= 360)
		degree -= 360;
	return (degree);
}

double	within_two_pi(double radians)
{
	if (radians < 0)
		radians += 2 * M_PI;
	else if (radians >= 2 * M_PI)
		radians -= 2 * M_PI;
	return (radians);
}

double	to_radians(double degrees)
{
	return (degrees * (M_PI / 180));
}

double	dist_between(vector_t a, dvector_t b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

double	dist_between_d_vectors(dvector_t a, dvector_t b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

double	lerp(double to_start, double to_end, double from_start, double from_end, double value)
{
	return (to_start + (to_end - to_start) * ((value - from_start) / (from_end - from_start)));
}
