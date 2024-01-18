/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shrooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:17:34 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	load_png(t_cub3d *cub3d)
{
	cub3d->shroom->shroom.texture = mlx_load_png(TEXTURE_MUSHROOM_COUNTER);
	if (!cub3d->shroom->shroom.texture)
		return (FAIL);
	return (SUCCESS);
}

static int	init_images(t_cub3d *cub3d)
{
	cub3d->shroom->shroom.img
		= mlx_texture_to_image(cub3d->mlx, cub3d->shroom->shroom.texture);
	if (!cub3d->shroom->shroom.img)
		return (FAIL);
	return (SUCCESS);
}

static void	set_position(t_cub3d *cub3d)
{
	cub3d->shroom->shroom.pos.x = cub3d->mlx->width
		* 0.95 - cub3d->shroom->shroom.img->width;
	cub3d->shroom->shroom.pos.y = cub3d->mlx->height
		* 0.95 - cub3d->shroom->shroom.img->height;
}

static int	put_image_to_window(t_cub3d *cub3d)
{
	if (mlx_image_to_window(cub3d->mlx, cub3d->shroom->shroom.img,
			cub3d->shroom->shroom.pos.x, cub3d->shroom->shroom.pos.y) == -1)
		return (FAIL);
	return (SUCCESS);
}

int	init_shroom(t_cub3d *cub3d)
{
	cub3d->shroom = ft_calloc(1, sizeof(t_shroom));
	if (!load_png(cub3d))
		return (FAIL);
	if (!init_images(cub3d))
		return (FAIL);
	set_position(cub3d);
	if (!put_image_to_window(cub3d))
		return (FAIL);
	disable_shroom(cub3d);
	return (SUCCESS);
}
