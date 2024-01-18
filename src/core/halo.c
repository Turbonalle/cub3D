/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:28:08 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:24 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	init_halo(t_cub3d *cub3d)
{
	cub3d->halo.img = mlx_new_image(cub3d->mlx,
			cub3d->img->width,
			cub3d->img->height);
	if (!cub3d->halo.img)
		return (err("Failed to create halo image"));
	if (mlx_image_to_window(cub3d->mlx, cub3d->halo.img, 0, 0) < 0)
		return (err("Failed to add halo to window"));
	cub3d->halo.img->instances[0].enabled = FALSE;
	cub3d->halo.active = FALSE;
	cub3d->halo.color = 0;
	cub3d->halo.timestamp = 0;
	return (SUCCESS);
}

void	activate_halo(t_halo *halo, int color)
{
	halo->img->instances[0].enabled = TRUE;
	halo->active = TRUE;
	halo->color = color;
	halo->timestamp = mlx_get_time();
}

static int	halo_is_active(t_halo *halo)
{
	return (mlx_get_time() - halo->timestamp < HALO_TIME);
}

void	handle_halo(t_halo *halo)
{
	if (halo->active)
	{
		if (halo_is_active(halo))
			draw_halo(halo->img, halo);
		else
		{
			halo->img->instances[0].enabled = FALSE;
			halo->active = FALSE;
		}
	}
}
