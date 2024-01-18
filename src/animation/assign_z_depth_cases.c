/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_z_depth_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 17:25:03 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:48:38 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	case_all_3(
	t_enemy **enemies, t_key_node **keys, t_distraction **distractions,
	t_four_vector *indexes)
{
	if (largest(enemies[indexes->e]->dist_to_player,
			keys[indexes->k]->dist_to_player,
			distractions[indexes->d]->dist_to_player) == 1)
	{
		enemies[indexes->e]->img_curr_frame->instances[0].z = indexes->z;
		indexes->e++;
	}
	else if (largest(enemies[indexes->e]->dist_to_player,
			keys[indexes->k]->dist_to_player,
			distractions[indexes->d]->dist_to_player) == 2)
	{
		keys[indexes->k]->img_curr_frame->instances[0].z = indexes->z;
		indexes->k++;
	}
	else
	{
		distractions[indexes->d]->img_distraction->instances[0].z = indexes->z;
		indexes->d++;
	}
}

void	case_without_keys(t_enemy **enemies, t_distraction **distractions,
	t_four_vector *indexes)
{
	if (enemies[indexes->e]->dist_to_player
		> distractions[indexes->d]->dist_to_player)
	{
		enemies[indexes->e]->img_curr_frame->instances[0].z = indexes->z;
		indexes->e++;
	}
	else
	{
		distractions[indexes->d]->img_distraction->instances[0].z = indexes->z;
		indexes->d++;
	}
}

void	case_without_distractions(t_enemy **enemies, t_key_node **keys,
	t_four_vector *indexes)
{
	if (enemies[indexes->e]->dist_to_player > keys[indexes->k]->dist_to_player)
	{
		enemies[indexes->e]->img_curr_frame->instances[0].z = indexes->z;
		indexes->e++;
	}
	else
	{
		keys[indexes->k]->img_curr_frame->instances[0].z = indexes->z;
		indexes->k++;
	}
}

void	case_without_enemies(t_key_node **keys,
	t_distraction **distractions, t_four_vector *indexes)
{
	if (keys[indexes->k]->dist_to_player
		> distractions[indexes->d]->dist_to_player)
	{
		keys[indexes->k]->img_curr_frame->instances[0].z = indexes->z;
		indexes->k++;
	}
	else
	{
		distractions[indexes->d]->img_distraction->instances[0].z = indexes->z;
		indexes->d++;
	}
}
