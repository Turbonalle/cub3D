/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slider.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:27:19 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/18 09:53:07 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_slider_line(mlx_image_t *img, t_slider *slider)
{
	int		x;
	int		y;

	y = slider->pos.y - img->instances[0].y - 1;
	while (++y < slider->pos.y - img->instances[0].y + SLIDER_LINE_WIDTH)
	{
		x = slider->pos.x - img->instances[0].x - 1;
		while (++x < slider->pos.x - img->instances[0].x + slider->length)
			mlx_put_pixel(img, x, y, SLIDER_LINE_COLOR);
	}
}

void	draw_slider_ends(mlx_image_t *img, t_slider *slider)
{
	int		x;
	int		y;

	y = slider->pos.y - img->instances[0].y + SLIDER_LINE_WIDTH
		/ 2 - SLIDER_MARKER_HEIGHT / 2 - 1;
	while (++y < slider->pos.y - img->instances[0].y + SLIDER_LINE_WIDTH
		/ 2 + SLIDER_MARKER_HEIGHT / 2)
	{
		x = slider->pos.x - img->instances[0].x - 1;
		while (++x < slider->pos.x - img->instances[0].x + SLIDER_LINE_WIDTH)
			mlx_put_pixel(img, x, y, SLIDER_LINE_COLOR);
		x = slider->pos.x - img->instances[0].x - 1 + slider->length
			- SLIDER_LINE_WIDTH;
		while (++x < slider->pos.x - img->instances[0].x + slider->length)
			mlx_put_pixel(img, x, y, SLIDER_LINE_COLOR);
	}
}

void	draw_slider(mlx_image_t *img, t_slider *slider)
{
	draw_slider_line(img, slider);
	draw_slider_ends(img, slider);
	draw_background(slider->marker, SLIDER_MARKER_COLOR);
}
