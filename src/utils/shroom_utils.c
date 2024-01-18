/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shroom_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:45:52 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_shroom_count(t_cub3d *cub3d)
{
	char	*text;

	if (cub3d->player.mushroom_count == 0)
	{
		if (cub3d->shroom->text)
			mlx_delete_image(cub3d->mlx, cub3d->shroom->text);
		disable_shroom(cub3d);
		return ;
	}
	text = ft_itoa(cub3d->player.mushroom_count);
	if (!text)
		return ;
	if (cub3d->shroom->text)
		mlx_delete_image(cub3d->mlx, cub3d->shroom->text);
	cub3d->shroom->text = mlx_put_string(cub3d->mlx, text,
			cub3d->mlx->width * 0.955, cub3d->shroom->shroom.pos.y
			+ 0.3 * (cub3d->shroom->shroom.img->height));
	free(text);
}

void	disable_shroom(t_cub3d *cub3d)
{
	if (cub3d->shroom->text)
		mlx_delete_image(cub3d->mlx, cub3d->shroom->text);
	cub3d->shroom->shroom.img->instances[0].enabled = FALSE;
}

void	enable_shroom(t_cub3d *cub3d)
{
	cub3d->shroom->shroom.img->instances[0].enabled = TRUE;
}
