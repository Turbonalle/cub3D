/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:32:01 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/18 09:53:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_rectangle(mlx_image_t *img, t_rectangle *rect)
{
	int	row;
	int	column;

	row = rect->pos.y - 1;
	while (++row < rect->pos.y + rect->height)
	{
		column = rect->pos.x - 1;
		while (++column < rect->pos.x + rect->width)
			mlx_put_pixel(img, column, row, rect->color);
	}
}

static void	set_box_bg_color(t_box *box)
{
	if (box->state == TRUE)
		box->background_color = BOX_ON_COLOR;
	else
		box->background_color = BOX_OFF_COLOR;
}

void	draw_checkbox(t_cub3d *cub3d, t_box *box)
{
	int	row;
	int	column;

	set_box_bg_color(box);
	row = box->pos.y;
	while (++row < box->pos.y + box->size)
	{
		column = box->pos.x;
		while (++column < box->pos.x + box->size)
		{
			if (row < box->pos.y + box->border_width
				|| row > box->pos.y + box->size - box->border_width)
				mlx_put_pixel(cub3d->pause_menu.menu, column, row,
					box->border_color);
			else if (column < box->pos.x + box->border_width
				|| column > box->pos.x + box->size - box->border_width)
				mlx_put_pixel(cub3d->pause_menu.menu, column, row,
					box->border_color);
			else
				mlx_put_pixel(cub3d->pause_menu.menu, column, row,
					box->background_color);
		}
	}
}

void	draw_hovered_checkbox(t_cub3d *cub3d, t_box *box)
{
	int	row;
	int	column;

	set_box_bg_color(box);
	row = box->pos.y;
	while (++row < box->pos.y + box->size)
	{
		column = box->pos.x;
		while (++column < box->pos.x + box->size)
		{
			if (row < box->pos.y + box->border_width
				|| row > box->pos.y + box->size - box->border_width)
				mlx_put_pixel(cub3d->pause_menu.menu, column, row,
					box->border_color);
			else if (column < box->pos.x + box->border_width
				|| column > box->pos.x + box->size - box->border_width)
				mlx_put_pixel(cub3d->pause_menu.menu, column, row,
					box->border_color);
			else
				mlx_put_pixel(cub3d->pause_menu.menu, column, row,
					box->background_color);
		}
	}
}
