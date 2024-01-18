/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:11:36 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/18 09:52:45 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_button(mlx_image_t *img, t_button *button)
{
	int	row;
	int	column;

	row = button->pos.y;
	while (row < button->pos.y + button->height)
	{
		column = button->pos.x;
		while (column < button->pos.x + button->width)
		{
			if (row < button->pos.y + button->border_width
				|| row >= button->pos.y + button->height
				- button->border_width
				|| column < button->pos.x + button->border_width
				|| column >= button->pos.x + button->width
				- button->border_width)
				mlx_put_pixel(img, column, row, button->border_color);
			else
				mlx_put_pixel(img, column, row, button->background_color);
			column++;
		}
		row++;
	}
}
