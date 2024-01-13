/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_hearts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:19 by slampine          #+#    #+#             */
/*   Updated: 2024/01/12 11:05:20 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	delete_full_heart_texture(cub3d_t *cub3d, int i)
{
	while (--i >= 0)
		mlx_delete_texture(cub3d->hearts[i].full.texture);
}

void	delete_empty_heart_texture(cub3d_t *cub3d, int i)
{
	while (--i >= 0)
		mlx_delete_texture(cub3d->hearts[i].empty.texture);
}

void	delete_full_heart_image(cub3d_t *cub3d, int i)
{
	while (--i >= 0)
		mlx_delete_image(cub3d->mlx, cub3d->hearts[i].full.img);
}

void	delete_empty_heart_image(cub3d_t *cub3d, int i)
{
	while (--i >= 0)
		mlx_delete_image(cub3d->mlx, cub3d->hearts[i].empty.img);
}

void	delete_hearts(cub3d_t *cub3d)
{
	delete_full_heart_texture(cub3d, HEARTS);
	delete_empty_heart_texture(cub3d, HEARTS);
	delete_full_heart_image(cub3d, HEARTS);
	delete_empty_heart_image(cub3d, HEARTS);
}