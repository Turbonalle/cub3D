/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_z_add_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:26:22 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:48:38 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	add_all_enemies(t_enemy **enemies, t_four_vector *indexes)
{
	while (enemies[indexes->e])
	{
		enemies[indexes->e]->img_curr_frame->instances[0].z = indexes->z;
		indexes->e++;
		indexes->z++;
	}
}

void	add_all_distractions(t_distraction **distractions,
	t_four_vector *indexes)
{
	while (distractions[indexes->d])
	{
		distractions[indexes->d]->img_distraction->instances[0].z = indexes->z;
		indexes->d++;
		indexes->z++;
	}
}

void	add_all_keys(t_key_node **keys, t_four_vector *indexes)
{
	while (keys[indexes->k])
	{
		keys[indexes->k]->img_curr_frame->instances[0].z = indexes->z;
		indexes->k++;
		indexes->z++;
	}
}
