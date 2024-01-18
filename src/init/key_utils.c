/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:21:11 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	add_key(t_cub3d *cub3d, int i, int j, int key_group_index)
{
	t_key_node	*new_key;

	new_key = ft_calloc(1, sizeof(t_key_node));
	if (!new_key)
		return (FAIL);
	new_key->pos.x = j + 0.5;
	new_key->pos.y = i + 0.5;
	new_key->collected = FALSE;
	new_key->next = cub3d->level->key_groups[key_group_index].keys;
	cub3d->level->key_groups[key_group_index].keys = new_key;
	return (SUCCESS);
}

int	init_key(t_cub3d *cub3d, int i, int j, int key_group_index)
{
	if (add_key(cub3d, i, j, key_group_index) == FAIL)
		return (FAIL);
	cub3d->level->door_groups[key_group_index].num_keys_left++;
	cub3d->level->key_groups[key_group_index].num_keys_total++;
	if (!draw_key_counts(cub3d))
		return (FAIL);
	return (SUCCESS);
}

int	get_key_index(char symbol)
{
	int	res;

	res = symbol - 'a';
	if (res < 0 || res >= NUM_DOORS_MAX)
		return (-1);
	return (res);
}

int	load_door_textures(t_cub3d *cub3d)
{
	cub3d->level->key_groups[0].texture_key_icon = mlx_load_png(TEXTURE_KEY_1);
	if (!cub3d->level->key_groups[0].texture_key_icon)
		return (0);
	cub3d->level->key_groups[1].texture_key_icon = mlx_load_png(TEXTURE_KEY_2);
	if (!cub3d->level->key_groups[1].texture_key_icon)
		return (0);
	cub3d->level->key_groups[2].texture_key_icon = mlx_load_png(TEXTURE_KEY_3);
	if (!cub3d->level->key_groups[2].texture_key_icon)
		return (0);
	cub3d->level->key_groups[3].texture_key_icon = mlx_load_png(TEXTURE_KEY_4);
	if (!cub3d->level->key_groups[3].texture_key_icon)
		return (0);
	cub3d->level->key_groups[0].texture_dir = FRAME_PATH_KEY_1;
	cub3d->level->key_groups[1].texture_dir = FRAME_PATH_KEY_2;
	cub3d->level->key_groups[2].texture_dir = FRAME_PATH_KEY_3;
	cub3d->level->key_groups[3].texture_dir = FRAME_PATH_KEY_4;
	return (1);
}

int	set_indexes(t_cub3d *cub3d, int i)
{
	int	j;
	int	door_key_index;

	while (cub3d->level->map[i])
	{
		j = 0;
		while (cub3d->level->map[i][j])
		{
			door_key_index = get_door_index(cub3d->level->map[i][j]);
			if (door_key_index != -1)
			{
				if (init_door(cub3d, i, j, door_key_index) == FAIL)
					return (FAIL);
			}
			door_key_index = get_key_index(cub3d->level->map[i][j]);
			if (door_key_index != -1)
			{
				if (init_key(cub3d, i, j, door_key_index) == FAIL)
					return (FAIL);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
