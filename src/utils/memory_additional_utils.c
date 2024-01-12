/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_additional_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:46:09 by slampine          #+#    #+#             */
/*   Updated: 2024/01/12 14:44:57 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

int	free_on_fail(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		free_doors(cub3d->level->door_groups[i].door_positions);
		if (cub3d->level->key_groups[i].texture_key_icon)
			mlx_delete_texture(cub3d->level->key_groups[i].texture_key_icon);
		free_keys(cub3d->level->key_groups[i].keys);
		i++;
	}
	return (0);
}

void	free_key_helper(cub3d_t *cub3d, int i)
{
	int			j;

	mlx_delete_image(cub3d->mlx,
		cub3d->level->key_groups[i].img_text_key_count);
	cub3d->level->key_groups[i].img_text_key_count = NULL;
	mlx_delete_image(cub3d->mlx, cub3d->level->key_groups[i].img_key_icon);
	cub3d->level->key_groups[i].img_key_icon = NULL;
	free_keys(cub3d->level->key_groups[i].keys);
	cub3d->level->key_groups[i].keys = NULL;
	j = 0;
	while (j < NUM_FRAMES_KEY)
	{
		mlx_delete_texture(cub3d->level->key_groups[i].textures_frames[j]);
		cub3d->level->key_groups[i].textures_frames[j] = NULL;
		j++;
	}
	free(cub3d->level->key_groups[i].textures_frames);
}

void	free_key_and_door_groups(cub3d_t *cub3d, int i)
{
	key_node_t	*tmp;

	free_doors(cub3d->level->door_groups[i].door_positions);
	cub3d->level->door_groups[i].door_positions = NULL;
	if (cub3d->level->key_groups[i].texture_key_icon)
		mlx_delete_texture(cub3d->level->key_groups[i].texture_key_icon);
	cub3d->level->key_groups[i].texture_key_icon = NULL;
	if (cub3d->level->key_groups[i].num_keys_total)
	{
		tmp = cub3d->level->key_groups[i].keys;
		while (tmp)
		{
			tmp->img_curr_frame->instances[0].enabled = FALSE;
			tmp = tmp->next;
		}
		free_key_helper(cub3d, i);
		cub3d->level->key_groups[i].textures_frames = NULL;
	}
}

void	free_keys_and_doors(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		free_key_and_door_groups(cub3d, i);
		i++;
	}
}
