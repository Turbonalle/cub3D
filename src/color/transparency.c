/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparency.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:25:58 by slampine          #+#    #+#             */
/*   Updated: 2023/11/15 14:44:26 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	set_transparency(int color, int transparency)
{
	float	alpha;

	alpha = 100 - transparency;
	if (alpha < 0)
		alpha = 0;
	else
		alpha *= 255 / 100;
	color = set_a(color, (int)alpha);
	return (color);
}
