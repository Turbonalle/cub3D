/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_frame_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:39:54 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:40:12 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	free_enemy_idle(t_cub3d *cub3d, int i)
{
	int	j;

	j = 0;
	while (j < NUM_FRAMES_ENEMY_IDLE)
	{
		if (cub3d->frames_idle[i][j])
			mlx_delete_texture(cub3d->frames_idle[i][j]);
		j++;
	}
}

void	free_enemy_walk(t_cub3d *cub3d, int i)
{
	int	j;

	j = 0;
	while (j < NUM_FRAMES_WALKING)
	{
		if (cub3d->frames_walking[i][j])
			mlx_delete_texture(cub3d->frames_walking[i][j++]);
		j++;
	}
}

void	free_enemy_hunt(t_cub3d *cub3d, int i)
{
	int	j;

	j = 0;
	while (j < NUM_FRAMES_HUNTING)
	{
		if (cub3d->frames_hunting[i][j])
			mlx_delete_texture(cub3d->frames_hunting[i][j++]);
		j++;
	}
}

void	free_enemy_frames(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_ENEMY_DIRECTIONS)
	{
		free_enemy_idle(cub3d, i);
		free_enemy_walk(cub3d, i);
		free_enemy_hunt(cub3d, i);
		i++;
	}
}
