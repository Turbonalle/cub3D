/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:57 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:38:02 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	min(int a, int b)
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
	while (radians < 0)
		radians += 2 * M_PI;
	while (radians >= 2 * M_PI)
		radians -= 2 * M_PI;
	return (radians);
}

double	to_radians(double degrees)
{
	return (degrees * (M_PI / 180));
}

double	dist_between(t_vector a, t_dvector b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}
