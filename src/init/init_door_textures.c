/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:32:25 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:11:28 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	free_textures_before_failed(t_texture *textures, int failed_index)
{
	int	i;

	i = 0;
	while (i < failed_index)
	{
		mlx_delete_texture(textures[i].texture);
		i++;
	}
}

void	nullify_star_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_FRAMES_STARS)
	{
		cub3d->stars[i].texture = NULL;
		i++;
	}
}

int	init_stars_textures(t_cub3d *cub3d)
{
	int	i;

	nullify_star_textures(cub3d);
	i = 0;
	while (i < NUM_FRAMES_STARS)
	{
		cub3d->stars[i].path = create_file_path(i, FRAME_PATH_STARS);
		if (!cub3d->stars[i].path)
		{
			free_textures_before_failed(cub3d->stars, i);
			return (err("Failed to malloc file path"));
		}
		cub3d->stars[i].texture = mlx_load_png(cub3d->stars[i].path);
		if (!cub3d->stars[i].texture)
		{
			free_textures_before_failed(cub3d->stars, i);
			return (err("Failed to load texture"));
		}
		i++;
	}
	return (SUCCESS);
}

static int	init_rest_door_textures(t_cub3d *cub3d)
{
	cub3d->door[3].texture = mlx_load_png(TEXTURE_DOOR_D);
	if (!cub3d->door[3].texture)
	{
		free_textures_before_failed(cub3d->door, 3);
		return (err("Failed to load texture"));
	}
	cub3d->door[4].texture = mlx_load_png(TEXTURE_DOOR_OPEN);
	if (!cub3d->door[4].texture)
	{
		free_textures_before_failed(cub3d->door, 4);
		return (err("Failed to load texture"));
	}
	return (SUCCESS);
}

int	init_door_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub3d->door[i].texture = NULL;
		i++;
	}
	cub3d->door[0].texture = mlx_load_png(TEXTURE_DOOR_A);
	cub3d->door[1].texture = mlx_load_png(TEXTURE_DOOR_B);
	if (!cub3d->door[1].texture)
	{
		free_textures_before_failed(cub3d->door, 1);
		return (err("Failed to load texture"));
	}
	cub3d->door[2].texture = mlx_load_png(TEXTURE_DOOR_C);
	if (!cub3d->door[2].texture)
	{
		free_textures_before_failed(cub3d->door, 2);
		return (err("Failed to load texture"));
	}
	if (!init_rest_door_textures(cub3d))
		return (FAIL);
	return (SUCCESS);
}
