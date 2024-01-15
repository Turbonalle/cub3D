/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_z_depth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:22 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 15:53:40 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	largest(three_vector_t *indexes)
{
	if (indexes->e > indexes->k)
	{
		if (indexes->e > indexes->d)
			return (1);
		if (indexes->d > indexes->e)
			return (3);
	}
	if (indexes->e > indexes->d)
	{
		if (indexes->k > indexes->e)
			return (2);
		if (indexes->e > indexes->k)
			return (1);
	}
	if (indexes->k > indexes->d)
	{
		if (indexes->e > indexes->k)
			return (1);
		if (indexes->k > indexes->e)
			return (2);
	}
	return (0);
}

void	add_all_enemies(t_enemy **enemies, three_vector_t *indexes)
{
	while (enemies[indexes->e])
	{
		enemies[indexes->e]->img_curr_frame->instances[0].z = indexes->z;
		indexes->e++;
		indexes->z++;
	}
}

void	add_all_distractions(distraction_t **distractions,
	three_vector_t *indexes)
{
	while (distractions[indexes->d])
	{
		distractions[indexes->d]->img_distraction->instances[0].z = indexes->z;
		indexes->d++;
		indexes->z++;
	}
}

void	add_all_keys(key_node_t **keys, three_vector_t *indexes)
{
	while (keys[indexes->k])
	{
		keys[indexes->k]->img_curr_frame->instances[0].z = indexes->z;
		indexes->k++;
		indexes->z++;
	}
}

void	case_all_3(
	t_enemy **enemies, key_node_t **keys, distraction_t **distractions,
	three_vector_t *indexes)
{
	if (largest(enemies[indexes->i]->dist_to_player,
			keys[indexes->j]->dist_to_player,
			distractions[indexes->k]->dist_to_player) == 1)
	{
		enemies[indexes->i]->img_curr_frame->instances[0].z = indexes->z;
		indexes->i++;
	}
	else if (largest(enemies[indexes->i]->dist_to_player,
			keys[indexes->j]->dist_to_player,
			distractions[indexes->k]->dist_to_player) == 2)
	{
		keys[indexes->j]->img_curr_frame->instances[0].z = indexes->z;
		indexes->j++;
	}
	else
	{
		distractions[indexes->k]->img_distraction->instances[0].z = indexes->z;
		indexes->k++;
	}
}

void	case_without_keys(t_enemy **enemies, distraction_t **distractions,
	three_vector_t *indexes)
{
	if (enemies[indexes->i]->dist_to_player
		> distractions[indexes->k]->dist_to_player)
	{
		enemies[indexes->i]->img_curr_frame->instances[0].z = indexes->z;
		indexes->i++;
	}
	else
	{
		distractions[indexes->k]->img_distraction->instances[0].z = indexes->z;
		indexes->k++;
	}
}

void	case_without_distractions(t_enemy **enemies, key_node_t **keys,
	three_vector_t *indexes)
{
	if (enemies[indexes->i]->dist_to_player > keys[indexes->j]->dist_to_player)
	{
		enemies[indexes->i]->img_curr_frame->instances[0].z = indexes->z;
		indexes->i++;
	}
	else
	{
		keys[indexes->j]->img_curr_frame->instances[0].z = indexes->z;
		indexes->j++;
	}
}

void	case_without_enemies(key_node_t **keys,
	distraction_t **distractions, three_vector_t *indexes)
{
	if (keys[indexes->j]->dist_to_player
		> distractions[indexes->k]->dist_to_player)
	{
		keys[indexes->j]->img_curr_frame->instances[0].z = indexes->z;
		indexes->j++;
	}
	else
	{
		distractions[indexes->k]->img_distraction->instances[0].z = indexes->z;
		indexes->k++;
	}
}

static void	init_indexes_and_z(cub3d_t *cub3d, three_vector_t *indexes)
{
	indexes->e = 0;
	indexes->k = 0;
	indexes->d = 0;
	indexes->z = cub3d->img->instances[0].z;
}

void	assign_z_depth_ordered_by_distance(cub3d_t *cub3d, t_enemy **enemies,
	key_node_t **keys, distraction_t **distractions)
{
	four_vector_t	indexes;

	init_indexes_and_z(&indexes);
	while (enemies[indexes.e] || keys[indexes.k] || distractions[indexes.d])
	{
		z++;
		if (enemies[indexes.e])
			if (keys[indexes.k])
				if (distractions[indexes.d])
					case_all_3(
						enemies, keys, distractions, &indexes);
				else
					case_without_distractions(enemies, keys, &indexes);
			else if (distractions[indexes.d])
				case_without_keys(enemies, distractions, &indexes);
			else
				add_all_enemies(enemies, &indexes);
		else if (keys[indexes.k])
			if (distractions[indexes.d])
				case_without_enemies(keys, distractions, &indexes);
			else
				add_all_keys(keys, &indexes);
		else
			add_all_distractions(distractions, &indexes);
	}
}
