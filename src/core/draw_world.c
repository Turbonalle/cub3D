/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:25:41 by slampine          #+#    #+#             */
/*   Updated: 2023/11/15 14:45:12 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

double	lerp(double y0, double y1, double x0, double x1, double x)
{
	return (y0 + (y1 - y0) * ((x - x0) / (x1 - x0)));
}

void	draw_world(cub3d_t *cub3d)
{
	int			index;
	int			color;
	double		min_dist;
	double		max_dist;
	double		height;
	dvector_t	start;
	dvector_t	end;

	min_dist = 0;
	max_dist = 20;
	index = -1;
	while (++index < (int)cub3d->img->width)
	{
		if (cub3d->rays[index].length < min_dist)
			height = cub3d->img->height;
		else if (cub3d->rays[index].length > max_dist)
			height = 0;
		else
			height = lerp(cub3d->img->height, 0, min_dist, max_dist, cub3d->rays[index].length);
		start.x = index;
		start.y = (cub3d->img->height - height) / 2;
		end.x = index;
		end.y = (cub3d->img->height + height) / 2;
		if (cub3d->rays[index].wall == EA)
			color = BLUE;
		else if (cub3d->rays[index].wall == SO)
			color = RED;
		else if (cub3d->rays[index].wall == WE)
			color = GREEN;
		else if (cub3d->rays[index].wall == NO)
			color = YELLOW;
		else
			color = WHITE;
		draw_line(cub3d->img, start, end, color);
	}
}
