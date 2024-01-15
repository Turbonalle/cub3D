/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_z_depth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:22 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 13:12:39 by vvagapov         ###   ########.fr       */
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

/* int	add_all_enemies(t_enemy **enemies, int index, int z)
{
	int	i;

	i = 0;
	while (i < cub3d->num_enemies)
	{
		if (add_enemy(cub3d, &cub3d->enemy[i]) == FAIL)
			return (FAIL);
		enemies[i] = &cub3d->enemy[i];
		i++;
	}
	return (SUCCESS);
} */

void assign_z_depth_by_distance_case_all_3_present(
	t_enemy **enemies, key_node_t **keys, distraction_t **distractions,
	int *i, int *j, int *k, int z)
{
	if (largest(enemies[*i]->dist_to_player, keys[*j]->dist_to_player, distractions[*k]->dist_to_player) == 1)
	{
		enemies[*i]->img_curr_frame->instances->z = z;
		(*i)++;
	}
	else if (largest(enemies[*i]->dist_to_player, keys[*j]->dist_to_player, distractions[*k]->dist_to_player) == 2)
	{
		keys[*j]->img_curr_frame->instances->z = z;
		(*j)++;
	}
	else
	{
		distractions[*k]->img_distraction->instances->z = z;
		(*k)++;
	}
}

void assign_z_depth_ordered_by_distance(cub3d_t *cub3d, t_enemy **enemies,
	key_node_t **keys, distraction_t **distractions)
{
	int	i;
	int	j;
	int	k;
	int	z;

	i = 0;
	j = 0;
	k = 0;
	// Start from z position of the main image
	z = cub3d->img->instances[0].z;
	while (enemies[i] || keys[j] || distractions[k])
	{
		z++;
		if (enemies[i])
		{
			if (keys[j])
			{
				if (distractions[k])
				{
					assign_z_depth_by_distance_case_all_3_present(
						enemies, keys, distractions, &i, &j, &k, z);
				}
				else
				{
					if (enemies[i]->dist_to_player > keys[j]->dist_to_player)
					{
						enemies[i]->img_curr_frame->instances->z = z;
						i++;
					}
					else
					{
						keys[j]->img_curr_frame->instances->z = z;
						j++;
					}
				}
			}
			else if (distractions[k])
			{
				if (enemies[i]->dist_to_player > distractions[k]->dist_to_player)
				{
					enemies[i]->img_curr_frame->instances->z = z;
					i++;
				}
				else
				{
					distractions[k]->img_distraction->instances->z = z;
					k++;
				}
			}
			else
			{
				while (enemies[i])
				{
					enemies[i]->img_curr_frame->instances->z = z;
					i++;
					z++;
				}
			}
		}
		else if (keys[j])
		{
			if (distractions[k])
			{
				if (keys[j]->dist_to_player > distractions[k]->dist_to_player)
				{
					keys[j]->img_curr_frame->instances->z = z;
					j++;
				}
				else
				{
					distractions[k]->img_distraction->instances->z = z;
					k++;
				}
			}
			else
			{
				while (keys[j])
				{
					keys[j]->img_curr_frame->instances->z = z;
					z++;
					j++;
				}
			}
		}
		else
		{
			while (distractions[k])
			{
				distractions[k]->img_distraction->instances->z = z;
				k++;
				z++;
			}
		}
	}
}


/* void assign_z_depth_ordered_by_distance(cub3d_t *cub3d, t_enemy **enemies,
	key_node_t **keys, distraction_t **distractions)
{
	int	i;
	int	j;
	int	k;
	int	z;

	i = 0;
	j = 0;
	k = 0;
	// Start from z position of the main image
	z = cub3d->img->instances[0].z;
	while (enemies[i] || keys[j] || distractions[k])
	{
		z++;
		if (enemies[i])
		{
			if (keys[j])
			{
				if (distractions[k])
				{
					if (largest(enemies[i]->dist_to_player, keys[j]->dist_to_player, distractions[k]->dist_to_player) == 1)
					{
						enemies[i]->img_curr_frame->instances->z = z;
						i++;
					}
					else if (largest(enemies[i]->dist_to_player, keys[j]->dist_to_player, distractions[k]->dist_to_player) == 2)
					{
						keys[j]->img_curr_frame->instances->z = z;
						j++;
					}
					else
					{
						distractions[k]->img_distraction->instances->z = z;
						k++;
					}
				}
				else
				{
					if (enemies[i]->dist_to_player > keys[j]->dist_to_player)
					{
						enemies[i]->img_curr_frame->instances->z = z;
						i++;
					}
					else
					{
						keys[j]->img_curr_frame->instances->z = z;
						j++;
					}
				}
			}
			else if (distractions[k])
			{
				if (enemies[i]->dist_to_player > distractions[k]->dist_to_player)
				{
					enemies[i]->img_curr_frame->instances->z = z;
					i++;
				}
				else
				{
					distractions[k]->img_distraction->instances->z = z;
					k++;
				}
			}
			else
			{
				while (enemies[i])
				{
					enemies[i]->img_curr_frame->instances->z = z;
					i++;
					z++;
				}
			}
		}
		else if (keys[j])
		{
			if (distractions[k])
			{
				if (keys[j]->dist_to_player > distractions[k]->dist_to_player)
				{
					keys[j]->img_curr_frame->instances->z = z;
					j++;
				}
				else
				{
					distractions[k]->img_distraction->instances->z = z;
					k++;
				}
			}
			else
			{
				while (keys[j])
				{
					keys[j]->img_curr_frame->instances->z = z;
					z++;
					j++;
				}
			}
		}
		else
		{
			while (distractions[k])
			{
				distractions[k]->img_distraction->instances->z = z;
				k++;
				z++;
			}
		}
	}
} */