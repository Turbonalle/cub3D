/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_distractions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:28 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:48:38 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	position_distraction(t_distraction *distr, mlx_texture_t *texture,
	double factor)
{
	distr->img_distraction->instances[0].x
		= distr->pos_screen.x - texture->width * factor * 0.5;
	distr->img_distraction->instances[0].y
		= distr->pos_screen.y - texture->height * factor * 1.5;
}

static void	scale_distraction(t_cub3d *cub3d, t_distraction *dist,
	mlx_texture_t *texture, double factor)
{
	t_uvector	src;
	t_uvector	res;
	int			ray;

	dist->img_distraction->instances[0].enabled = TRUE;
	empty_image(dist->img_distraction);
	res.row = 0;
	while (res.row++ < texture->height * factor)
	{
		res.col = 0;
		if (res.row < dist->img_distraction->height)
		{
			while (res.col++ < texture->width * factor)
			{
				if (res.col < dist->img_distraction->width)
				{
					set_src_coordinates(&src, res, factor, texture);
					ray = get_ray_i(dist->pos_screen.x, texture, factor, res);
					if (column_visible(cub3d, dist->dist_to_player, ray))
						copy_pixel(dist->img_distraction, res, texture, src);
				}
			}
		}
	}
	position_distraction(dist, texture, factor);
}

static void	draw_distraction_frame(t_cub3d *cub3d, t_distraction *distr)
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

void	draw_all_distractions(t_cub3d *cub3d, t_distraction **distractions)
{
	int	i;

	i = 0;
	while (distractions[i])
	{
		draw_distraction_frame(cub3d, distractions[i]);
		i++;
	}
}
