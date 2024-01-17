/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:30 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/17 14:11:31 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_background(mlx_image_t *img, int color)
{
	unsigned int	row;
	unsigned int	column;

	row = -1;
	while (++row < img->height)
	{
		column = -1;
		while (++column < img->width)
		{
			if (row < img->height / 2)
				mlx_put_pixel(img, column, row, color);
			else
				mlx_put_pixel(img, column, row, color);
		}
	}
}
