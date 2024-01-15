/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_distractions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:28 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 21:28:15 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	position_distraction(distraction_t *distr, mlx_texture_t *texture,
	double factor)
{
	distr->img_distraction->instances[0].x
		= distr->pos_screen.x - texture->width * factor * 0.5;
	distr->img_distraction->instances[0].y
		= distr->pos_screen.y - texture->height * factor * 1.5;
}

static void	scale_distraction(cub3d_t *cub3d, distraction_t *dist,
	mlx_texture_t *texture, double factor)
{
	uvector_t	src;
	uvector_t	res;
	int			ray_i;

	dist->img_distraction->instances[0].enabled = TRUE;
	empty_image(dist->img_distraction);
	res.row = 0;
	while (res.row++ < texture->height * factor)
	{
		res.col = 0;
		if (res.row < dist->img_distraction->height)
		{
			while (res.col < texture->width * factor)
			{
				if (res.col++ < dist->img_distraction->width)
				{
					set_src_coordinates(&src, res, factor, texture);
					ray_i = get_ray_i(dist->pos_screen.x, texture, factor, res);
					if (column_visible(cub3d, dist->dist_to_player, ray_i))
						copy_pixel(dist->img_distraction, res, texture, src);
				}
			}
		}
	}
	position_distraction(dist, texture, factor);
}

static void	draw_distraction_frame(cub3d_t *cub3d, distraction_t *distr)
{
	double			scale_factor;
	mlx_texture_t	*texture;

	scale_factor = calculate_scale_factor(distr->dist_to_player,
			DISTRACTION_NORMAL_SCALE_DISTANCE);
	if (distr->thrown == TRUE)
		texture = cub3d->distraction_thrown_texture;
	else
		texture = cub3d->distraction_texture;
	scale_distraction
	(
		cub3d,
		distr,
		texture,
		scale_factor
	);
}

void	draw_all_distractions(cub3d_t *cub3d, distraction_t **distractions)
{
	int	i;

	i = 0;
	while (distractions[i])
	{
		draw_distraction_frame(cub3d, distractions[i]);
		i++;
	}
}
