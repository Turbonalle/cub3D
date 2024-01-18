/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:01:52 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/18 09:38:02 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_line(mlx_image_t *img, t_dvector start_d, t_dvector end_d,
	int color)
{
	t_vector	start;
	t_vector	end;

	start.x = start_d.x;
	start.y = start_d.y;
	end.x = round(end_d.x);
	end.y = round(end_d.y);
	if (start.x < 0 || start.x >= (int)img->width
		|| end.y < 0 || end.y >= (int)img->height)
		return ;
	if (start.x < end.x)
		end.x -= 1;
	if (start.y < end.y)
		end.y -= 1;
	bresenham(img, start, end, color);
}

void	draw_vertical_line(mlx_image_t *img, t_dvector start, t_dvector end,
	int color)
{
	int	y;

	y = (int)start.y;
	while (y <= end.y)
	{
		mlx_put_pixel(img, start.x, y, color);
		y++;
	}
}
