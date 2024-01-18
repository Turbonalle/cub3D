/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_additional_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:46:09 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	delete_heart(t_cub3d *cub3d)
{
	mlx_delete_texture(cub3d->level->heart.texture);
	mlx_delete_texture(cub3d->level->heart_half.texture);
	mlx_delete_texture(cub3d->level->heart_empty.texture);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_img);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_half_img);
	mlx_delete_image(cub3d->mlx, cub3d->level->heart_empty_img);
	cub3d->level->heart.texture = NULL;
	cub3d->level->heart_half.texture = NULL;
	cub3d->level->heart_empty.texture = NULL;
	cub3d->level->heart_img = NULL;
	cub3d->level->heart_half_img = NULL;
	cub3d->level->heart_empty_img = NULL;
}

int	free_on_fail(t_cub3d *cub3d)
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
	return (FAIL);
}

void	free_key_helper(t_cub3d *cub3d, int i)
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

void	free_key_and_door_groups(t_cub3d *cub3d, int i)
{
	t_key_node	*tmp;

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

void	free_keys_and_doors(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		free_key_and_door_groups(cub3d, i);
		i++;
	}
}
