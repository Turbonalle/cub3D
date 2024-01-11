/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:08:28 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 15:08:37 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	center(mlx_image_t *img)
{
	img->instances[0].x -= img->width * 0.5;
	img->instances[0].y -= img->height * 0.5;
}

void	center_vertically(mlx_image_t *img)
{
	img->instances[0].y -= img->height * 0.5;
}

void	center_horizontally(mlx_image_t *img)
{
	img->instances[0].x -= img->width * 0.5;
}
