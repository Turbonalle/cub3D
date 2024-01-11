/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_extra_plus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:32:47 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 13:46:49 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	free_distractions(cub3d_t *cub3d)
{
	int	i;

	if (cub3d->level->num_distractions)
	{
		i = 0;
		while (i < cub3d->level->num_distractions)
		{
			mlx_delete_image(cub3d->mlx,
				cub3d->level->distractions[i].img_distraction);
			cub3d->level->distractions[i].img_distraction = NULL;
			i++;
		}
		free(cub3d->level->distractions);
		cub3d->level->distractions = NULL;
	}
}

void	disable_items(cub3d_t *cub3d)
{
	cub3d->halo.img->instances[0].enabled = FALSE;
	disable_shroom(cub3d);
	disable_hearts(cub3d);
}

void	free_minimap(cub3d_t *cub3d)
{
	mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
}

void	free_level(cub3d_t *cub3d)
{
	free_keys_and_doors(cub3d);
	free_info(cub3d->level->map);
	free_enemies(cub3d);
	free_distractions(cub3d);
	free_minimap(cub3d);
	disable_items(cub3d);
}

void	free_level_without_textures(cub3d_t *cub3d)
{
	free_keys_and_doors(cub3d);
	free_info(cub3d->level->map);
	free_enemies(cub3d);
	free_distractions(cub3d);
	free_minimap(cub3d);
	disable_items(cub3d);
}
