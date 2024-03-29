/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:18:24 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:11:55 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	free_textures_before_failed_old(t_texture *textures, int failed_index)
{
	int	i;

	i = 0;
	while (i < failed_index)
	{
		free(textures[i].path);
		mlx_delete_texture(textures[i].texture);
		textures[i].path = NULL;
		textures[i].texture = NULL;
		i++;
	}
}

int	init_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub3d->level->texture[i].texture = NULL;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		cub3d->level->texture[i].texture
			= mlx_load_png(cub3d->level->texture[i].path);
		if (!cub3d->level->texture[i].texture)
		{
			free_textures_before_failed(cub3d->level->texture, i);
			return (err("Failed to load texture"));
		}
		i++;
	}
	return (SUCCESS);
}
