/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:15:10 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 12:24:11 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	add_door_pos(t_cub3d *cub3d, int i, int j, int door_group_index)
{
	t_door_pos	*new_pos;

	new_pos = ft_calloc(1, sizeof(t_door_pos));
	if (!new_pos)
		return (FAIL);
	new_pos->pos.x = j;
	new_pos->pos.y = i;
	new_pos->next = cub3d->level->door_groups[door_group_index].door_positions;
	cub3d->level->door_groups[door_group_index].door_positions = new_pos;
	return (SUCCESS);
}

int	init_door(t_cub3d *cub3d, int i, int j, int door_group_index)
{
	cub3d->level->door_groups[door_group_index].index = door_group_index;
	if (add_door_pos(cub3d, i, j, door_group_index) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	get_door_index(char symbol)
{
	int	res;

	res = symbol - 'A';
	if (res < 0 || res >= NUM_DOORS_MAX)
		return (-1);
	return (res);
}

void	init_door_values(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		cub3d->level->door_groups[i].index = i;
		cub3d->level->door_groups[i].door_positions = NULL;
		cub3d->level->door_groups[i].num_keys_left = 0;
		cub3d->level->key_groups[i].index = i;
		cub3d->level->key_groups[i].keys = NULL;
		cub3d->level->key_groups[i].num_keys_total = 0;
		cub3d->level->key_groups[i].curr_frame_index = 0;
		cub3d->level->key_groups[i].prev_frame_index = -1;
		cub3d->level->key_groups[i].img_key_icon = NULL;
		cub3d->level->key_groups[i].img_text_key_count = NULL;
		cub3d->level->key_groups[i].textures_frames = NULL;
		cub3d->level->key_groups[i].texture_key_icon = NULL;
		i++;
	}
}
