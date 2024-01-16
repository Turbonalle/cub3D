/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halo_fade.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:16:21 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 23:16:21 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	get_distance_from_edge(mlx_image_t *img,
	unsigned int row,
	unsigned int column)
{
	int	distance_from_edge;

	distance_from_edge = row;
	distance_from_edge = min(distance_from_edge, img->height - row);
	distance_from_edge = min(distance_from_edge, column);
	distance_from_edge = min(distance_from_edge, img->width - column);
	return (distance_from_edge);
}

static double	set_edge_fade(int distance_from_edge)
{
	double	edge_fade;

	if (distance_from_edge < HALO_THICKNESS)
		edge_fade = (double)distance_from_edge / HALO_THICKNESS;
	else
		edge_fade = 1;
	return (1 - edge_fade);
}

static int	set_fade(double time_fade, double edge_fade)
{
	int	fade;

	fade = roundf(time_fade * edge_fade * 100);
	return (100 - fade);
}

void	draw_halo(mlx_image_t *img, halo_t *halo)
{
	unsigned int	column;
	unsigned int	row;
	double			time_fade;
	int				distance_from_edge;
	int				color;

	time_fade = get_time_fade(halo);
	row = -1;
	while (++row < img->height)
	{
		column = -1;
		while (++column < img->width)
		{
			distance_from_edge = get_distance_from_edge(img, row, column);
			if (distance_from_edge < HALO_THICKNESS)
			{
				color = set_transparency(halo->color,
						set_fade(time_fade, set_edge_fade(distance_from_edge)));
				mlx_put_pixel(img, column, row, color);
			}
		}
	}
}
