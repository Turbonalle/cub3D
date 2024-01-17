/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:17:31 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/17 15:18:01 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	set_delta_low_slope(vector_t *delta, vector_t start, vector_t end,
	int *yi)
{
	delta->x = end.x - start.x;
	delta->y = end.y - start.y;
	*yi = 1;
	if (delta->y < 0)
	{
		*yi = -1;
		delta->y = -delta->y;
	}
}

static void	bresenham_low_slope(mlx_image_t *img, vector_t start, vector_t end,
	int color)
{
	vector_t	delta;
	vector_t	pixel;
	int			yi;
	int			decision_var;

	set_delta_low_slope(&delta, start, end, &yi);
	decision_var = (2 * delta.y) - delta.x;
	pixel.x = start.x;
	pixel.y = start.y;
	while (pixel.x <= end.x)
	{
		if (pixel.x >= 0 && pixel.x < (int)img->width && pixel.y >= 0
			&& pixel.y < (int)img->height)
			mlx_put_pixel(img, pixel.x, pixel.y, color);
		if (decision_var > 0)
		{
			pixel.y = pixel.y + yi;
			decision_var = decision_var + (2 * (delta.y - delta.x));
		}
		else
			decision_var = decision_var + 2 * delta.y;
		pixel.x++;
	}
}

static void	set_delta_high_slope(vector_t *delta, vector_t start, vector_t end,
	int *xi)
{
	delta->x = end.x - start.x;
	delta->y = end.y - start.y;
	*xi = 1;
	if (delta->x < 0)
	{
		*xi = -1;
		delta->x = -delta->x;
	}
}

static void	bresenham_high_slope(mlx_image_t *img, vector_t start, vector_t end,
	int color)
{
	vector_t	delta;
	vector_t	pixel;
	int			xi;
	int			decision_var;

	set_delta_high_slope(&delta, start, end, &xi);
	decision_var = (2 * delta.x) - delta.y;
	pixel.y = start.y;
	pixel.x = start.x;
	while (pixel.y <= end.y)
	{
		if (pixel.x >= 0 && pixel.x < (int)img->width
			&& pixel.y >= 0 && pixel.y < (int)img->height)
			mlx_put_pixel(img, pixel.x, pixel.y, color);
		if (decision_var > 0)
		{
			pixel.x = pixel.x + xi;
			decision_var = decision_var + (2 * (delta.x - delta.y));
		}
		else
			decision_var = decision_var + 2 * delta.x;
		pixel.y++;
	}
}

void	bresenham(mlx_image_t *img, vector_t start, vector_t end, int color)
{
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
