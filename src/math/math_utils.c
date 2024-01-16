/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:50:49 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 15:14:08 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

double	dist_between_d_vectors(dvector_t a, dvector_t b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

double	lerp(double to_start, double to_end, double from_start, double from_end, double value)
{
	return (to_start + (to_end - to_start) * ((value - from_start)
			/ (from_end - from_start)));
}
