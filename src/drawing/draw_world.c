/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:31 by slampine          #+#    #+#             */
/*   Updated: 2023/11/28 20:40:32 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

double lerp(double y0, double y1, double x0, double x1, double x)
{
	return (y0 + (y1 - y0) * ((x - x0) / (x1 - x0)));
}

void draw_world(cub3d_t *cub3d)
{
	int		index;
	int		color;
	double	min_dist;
	double	max_dist;
	double	height;
	double	roomH;
	double	screenH;
	double	fovArc;
	double	perpD;
	dvector_t start;
	dvector_t end;

	min_dist = 0;
	max_dist = 100;
	index = -1;
	roomH = 3;

	while (++index < (int)cub3d->img->width)
	{
		if (cub3d->rays[index].length < min_dist)
			height = cub3d->img->height;
		else if (cub3d->rays[index].length > max_dist)
			height = 0;
		else
		{
			{
				if (cub3d->settings.fisheye)
				{
					fovArc = M_PI * 2 * cub3d->rays[index].length * cub3d->fov / 360.0;
					screenH = 1.0 / fovArc * cub3d->img->width * roomH;
				}
				else
				{
					perpD = sqrt(pow(cub3d->player.pos.x - cub3d->rays[index].end.x, 2) + (pow(cub3d->player.pos.y - cub3d->rays[index].end.y, 2)));
					perpD = perpD * cos(to_radians(cub3d->rays[index].angle - cub3d->player.angle));
					screenH = floor(cub3d->img->height / perpD);
				}
				height = screenH;
				if (height > cub3d->img->height)
					height = cub3d->img->height;
			}
		}
		start.x = index;
		start.y = (cub3d->img->height - height) / 2;
		end.x = index;
		end.y = (cub3d->img->height + height) / 2;
		if (end.y == cub3d->img->height)
			end.y--;
		if (cub3d->rays[index].wall == EA)
		{
			color = BLUE;
		}
		else if (cub3d->rays[index].wall == SO)
		{
			color = RED;
		}
		else if (cub3d->rays[index].wall == WE)
		{
			color = GREEN;
		}
		else if (cub3d->rays[index].wall == NO)
		{
			color = YELLOW;
		}
		else if (cub3d->rays[index].wall == DE)
		{
			color = PURPLE;
		}
		else if (cub3d->rays[index].wall == DN)
		{
			color = CORAL;
		}
		else if (cub3d->rays[index].wall == 'A')
		{
			color = ORANGE_RED;
		}
		else if (cub3d->rays[index].wall == 'B')
		{
			color = SPRING_GREEN;
		}
		else if (cub3d->rays[index].wall == 'C')
		{
			color = GOLD;
		}
		else if (cub3d->rays[index].wall == 'D')
		{
			color = TEAL;
		}
		else
			color = WHITE;
		draw_vertical_line(cub3d->img, start, end, color);
	}
}
