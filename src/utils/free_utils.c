/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:33:59 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:48:24 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	free_backup(t_level level)
{
	int	i;

	i = 0;
	//TODO: Check for double free
	while (level.backup[i])
	{
		free(level.backup[i]);
		level.backup[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (level.texture[i].path)
			free(level.texture[i].path);
		level.texture[i].path = NULL;
		if (level.texture[i].texture)
			mlx_delete_texture(level.texture[i].texture);
		level.texture[i].texture = NULL;
		i++;
	}
	free(level.backup);
	level.backup = NULL;
}

void	free_level_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub3d->level->texture[i].texture)
			mlx_delete_texture(cub3d->level->texture[i].texture);
		cub3d->level->texture[i].texture = NULL;
		i++;
	}
}

void	free_enemies(t_cub3d *cub3d)
{
	int	i;

	if (cub3d->num_enemies)
	{
		i = 0;
		while (i < cub3d->num_enemies)
		{
			mlx_delete_image(cub3d->mlx, cub3d->enemy[i].img_curr_frame);
			cub3d->enemy[i].img_curr_frame = NULL;
			i++;
		}
		free(cub3d->enemy);
		cub3d->enemy = NULL;
		cub3d->num_enemies = 0;
	}
}
