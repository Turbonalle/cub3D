/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:50:49 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:38:18 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

double	dist_between_d_vectors(t_dvector a, t_dvector b)
{
	return (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
}

double	lerp(t_range to, t_range from, double value)
{
	return (to.start + (to.end - to.start) * ((value - from.start)
			/ (from.end - from.start)));
}
