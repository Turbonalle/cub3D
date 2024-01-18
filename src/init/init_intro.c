/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_intro.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:29:28 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	init_intro(t_cub3d *cub3d)
{
	cub3d->intro_watched = FALSE;
	cub3d->intro.texture = mlx_load_png(INTRO_PNG);
	if (!cub3d->intro.texture)
		return (FAIL);
	cub3d->intro.img = mlx_texture_to_image(cub3d->mlx, cub3d->intro.texture);
	if (!cub3d->intro.img)
	{
		mlx_delete_texture(cub3d->intro.texture);
		return (err("Failed to load intro image"));
	}
	if (mlx_image_to_window(cub3d->mlx, cub3d->intro.img, 0, 0) < 0)
	{
		mlx_delete_texture(cub3d->intro.texture);
		return (err("Failed to put intro image to window"));
	}
	disable_intro(cub3d);
	return (SUCCESS);
}
