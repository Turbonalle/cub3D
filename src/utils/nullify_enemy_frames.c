/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nullify_enemy_frames.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:58:06 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 08:58:07 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	nullify_idle_frames(mlx_texture_t **frames_idle)
{
	int	i;

	i = -1;
	while (++i < NUM_FRAMES_ENEMY_IDLE)
		frames_idle[i] = NULL;
}

static void	nullify_walking_frames(mlx_texture_t **frames_walking)
{
	int	i;

	i = -1;
	while (++i < NUM_FRAMES_ENEMY_WALKING)
		frames_walking[i] = NULL;
}

void	nullify_enemy_frames(cub3d_t *cub3d)
{
	int	i;

	i = -1;
	while (++i < NUM_ENEMY_DIRECTIONS)
	{
		cub3d->frames_idle_paths[i] = NULL;
		cub3d->frames_walking_paths[i] = NULL;
		nullify_idle_frames(cub3d->frames_idle[i]);
		nullify_walking_frames(cub3d->frames_walking[i]);
	}
}
