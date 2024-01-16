/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_z_add_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:26:22 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 17:26:40 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	add_all_enemies(t_enemy **enemies, four_vector_t *indexes)
{
	while (enemies[indexes->e])
	{
		enemies[indexes->e]->img_curr_frame->instances[0].z = indexes->z;
		indexes->e++;
		indexes->z++;
	}
}

void	add_all_distractions(distraction_t **distractions,
	four_vector_t *indexes)
{
	while (distractions[indexes->d])
	{
		distractions[indexes->d]->img_distraction->instances[0].z = indexes->z;
		indexes->d++;
		indexes->z++;
	}
}

void	add_all_keys(key_node_t **keys, four_vector_t *indexes)
{
	while (keys[indexes->k])
	{
		keys[indexes->k]->img_curr_frame->instances[0].z = indexes->z;
		indexes->k++;
		indexes->z++;
	}
}
