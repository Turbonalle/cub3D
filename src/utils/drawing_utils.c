/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:58:51 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:37:42 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_square(mlx_image_t *img, t_vector coord, int size, int color)
{
	t_vector	end;
	int			x;

	end.x = coord.x + size;
	end.y = coord.y + size;
	x = coord.x;
	while (coord.y < end.y)
	{
		coord.x = x;
		while (coord.x < end.x)
		{
			mlx_put_pixel(img, coord.x, coord.y, color);
			coord.x++;
		}
		coord.y++;
	}
}

void	draw_lines(mlx_image_t *img, t_vector center, t_vector pos, int color)
{
	int	start;

	start = center.x - pos.x;
	while (start <= center.x + pos.x)
	{
		mlx_put_pixel(img, start, center.y + pos.y, color);
		mlx_put_pixel(img, start, center.y - pos.y, color);
		start++;
	}
	start = center.x - pos.y;
	while (start <= center.x + pos.y)
	{
		mlx_put_pixel(img, start, center.y + pos.x, color);
		mlx_put_pixel(img, start, center.y - pos.x, color);
		start++;
	}
}

void	draw_circle(mlx_image_t *img, t_vector pos, int radius, int color)
{
	t_vector	center;
	t_vector	new_pos;
	int			decision;

	center.x = pos.x + radius;
	center.y = pos.y + radius;
	new_pos.x = radius;
	new_pos.y = 0;
	decision = 1 - radius;
	while (new_pos.x >= new_pos.y)
	{
		draw_lines(img, center, new_pos, color);
		new_pos.y++;
		if (decision <= 0)
			decision += 2 * new_pos.y + 1;
		else
		{
			new_pos.x--;
			decision += 2 * (new_pos.y - new_pos.x) + 1;
		}
	}
}
