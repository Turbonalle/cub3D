/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_z_depth_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:25:41 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	largest(double i, double j, double k)
{
	if (i > j)
	{
		if (i > k)
			return (1);
		if (k > i)
			return (3);
	}
	if (i > k)
	{
		if (j > i)
			return (2);
		if (i > j)
			return (1);
	}
	if (j > k)
	{
		if (i > j)
			return (1);
		if (j > i)
			return (2);
	}
	return (0);
}

void	init_indexes_and_z(t_cub3d *cub3d, t_four_vector *indexes)
{
	indexes->e = 0;
	indexes->k = 0;
	indexes->d = 0;
	indexes->z = cub3d->img->instances[0].z;
}
