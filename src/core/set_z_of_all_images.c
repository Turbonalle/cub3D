/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_z_of_all_images.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:44:41 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	count_all_keys(t_cub3d *cub3d)
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		count += cub3d->level->key_groups[i].num_keys_total;
		i++;
	}
	return (count);
}

static int	set_z_for_key_groups(t_cub3d *cub3d, int starting_z)
{
	int			i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->key_groups[i].num_keys_total)
		{
			cub3d->level->key_groups[i]
				.img_key_icon->instances[0].z = starting_z;
			starting_z++;
			cub3d->level->key_groups[i]
				.img_text_key_count->instances[0].z = starting_z;
			starting_z++;
		}
		i++;
	}
	return (starting_z);
}

void	set_z_of_all_images(t_cub3d *cub3d)
{
	int	z;

	z = 0;
	cub3d->img->instances[0].z = z;
	z++;
	z += count_all_keys(cub3d);
	z += cub3d->num_enemies;
	z += cub3d->level->num_distractions;
	z += set_z_for_key_groups(cub3d, z);
	cub3d->minimap.img->instances[0].z = z;
	z++;
}
