/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:55 by slampine          #+#    #+#             */
/*   Updated: 2023/12/05 19:00:37 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void bresenham_low_slope(mlx_image_t *img, vector_t start, vector_t end, int color)
{
	vector_t delta;
	vector_t pixel;
	int yi;
	int D;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	yi = 1;
	if (delta.y < 0)
	{
		yi = -1;
		delta.y = -delta.y;
	}
	D = (2 * delta.y) - delta.x;
	pixel.x = start.x;
	pixel.y = start.y;
	while (pixel.x <= end.x)
	{
		mlx_put_pixel(img, pixel.x, pixel.y, color);
		if (D > 0)
		{
			pixel.y = pixel.y + yi;
			D = D + (2 * (delta.y - delta.x));
		}
		else
			D = D + 2 * delta.y;
		pixel.x++;
	}
}

void bresenham_high_slope(mlx_image_t *img, vector_t start, vector_t end, int color)
{
	vector_t	delta;
	vector_t	pixel;
	int			xi;
	int			D;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	xi = 1;
	if (delta.x < 0)
	{
		xi = -1;
		delta.x = -delta.x;
	}
	D = (2 * delta.x) - delta.y;
	pixel.y = start.y;
	pixel.x = start.x;
	while (pixel.y <= end.y)
	{
		mlx_put_pixel(img, pixel.x, pixel.y, color);
		if (D > 0)
		{
			pixel.x = pixel.x + xi;
			D = D + (2 * (delta.x - delta.y));
		}
		else
			D = D + 2 * delta.x;
		pixel.y++;
	}
}

void	draw_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color)
{
	vector_t	start;
	vector_t	end;

	start.x = start_d.x;
	start.y = start_d.y;
	end.x = end_d.x;
	end.y = end_d.y;
	if (abs(end.y - start.y) < abs(end.x - start.x))
	{
		if (start.x > end.x)
			bresenham_low_slope(img, end, start, color);
		else
			bresenham_low_slope(img, start, end, color);
	}
	else
	{
		if (start.y > end.y)
			bresenham_high_slope(img, end, start, color);
		else
			bresenham_high_slope(img, start, end, color);
	}
}

void draw_vertical_line(mlx_image_t *img, dvector_t start_d, dvector_t end_d, int color)
{
	vector_t	start;
	vector_t	end;

	start.x = start_d.x;
	start.y = start_d.y;
	end.x = end_d.x;
	end.y = end_d.y;
	while (start.y <= end.y)
	{
		mlx_put_pixel(img, start.x, start.y, color);
		start.y++;
	}
}
