/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_z_depth_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:25:41 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 17:27:02 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	largest(double i, double j, double k)
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

static void	init_indexes_and_z(cub3d_t *cub3d, four_vector_t *indexes)
{
	indexes->e = 0;
	indexes->k = 0;
	indexes->d = 0;
	indexes->z = cub3d->img->instances[0].z;
}
