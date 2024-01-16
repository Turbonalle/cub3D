/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_z_depth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:22 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 17:26:48 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	assign_z_depth_ordered_by_distance(cub3d_t *cub3d, t_enemy **enemies,
	key_node_t **keys, distraction_t **distractions)
{
	four_vector_t	indexes;

	init_indexes_and_z(cub3d, &indexes);
	while (enemies[indexes.e] || keys[indexes.k] || distractions[indexes.d])
	{
		indexes.z++;
		if (enemies[indexes.e] && keys[indexes.k] && distractions[indexes.d])
			case_all_3(enemies, keys, distractions, &indexes);
		else if (enemies[indexes.e] && keys[indexes.k])
			case_without_distractions(enemies, keys, &indexes);
		else if (enemies[indexes.e] && distractions[indexes.d])
			case_without_keys(enemies, distractions, &indexes);
		else if (keys[indexes.k] && distractions[indexes.d])
			case_without_enemies(keys, distractions, &indexes);
		else if (enemies[indexes.e])
			add_all_enemies(enemies, &indexes);
		else if (keys[indexes.k])
			add_all_keys(keys, &indexes);
		else
			add_all_distractions(distractions, &indexes);
	}
}
