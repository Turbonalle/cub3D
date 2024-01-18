/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:10:56 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/18 09:47:10 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	draw_horizon(t_cub3d *cub3d)
{
	t_dvector	horizon_left;
	t_dvector	horizon_right;

	horizon_left.x = 0;
	horizon_left.y = cub3d->img->height / 2;
	horizon_right.x = cub3d->img->width;
	horizon_right.y = cub3d->img->height / 2;
	draw_line(cub3d->img, horizon_left, horizon_right, BLACK);
}

static void	set_frustum(t_cub3d *cub3d, t_frustum *frustum)
{
	frustum->half_fov = to_radians(cub3d->fov / 2);
	frustum->far_left.x = cub3d->player.pos.x + FRUSTUM_FAR
		* cos(cub3d->player.angle - frustum->half_fov);
	frustum->far_left.y = cub3d->player.pos.y + FRUSTUM_FAR
		* sin(cub3d->player.angle - frustum->half_fov);
	frustum->far_right.x = cub3d->player.pos.x + FRUSTUM_FAR
		* cos(cub3d->player.angle + frustum->half_fov);
	frustum->far_right.y = cub3d->player.pos.y + FRUSTUM_FAR
		* sin(cub3d->player.angle + frustum->half_fov);
	frustum->near_left.x = cub3d->player.pos.x + FRUSTUM_NEAR
		* cos(cub3d->player.angle - frustum->half_fov);
	frustum->near_left.y = cub3d->player.pos.y + FRUSTUM_NEAR
		* sin(cub3d->player.angle - frustum->half_fov);
	frustum->near_right.x = cub3d->player.pos.x + FRUSTUM_NEAR
		* cos(cub3d->player.angle + frustum->half_fov);
	frustum->near_right.y = cub3d->player.pos.y + FRUSTUM_NEAR
		* sin(cub3d->player.angle + frustum->half_fov);
}

static void	set_frustum_vectors(t_cub3d *cub3d, t_frustum *frustum, int y)
{
	double	sample_height;

	sample_height = (double)y / ((double)cub3d->img->height / 2);
	if (sample_height == 0)
	{
		frustum->left.x = frustum->near_left.x;
		frustum->left.y = frustum->near_left.y;
		frustum->right.x = frustum->near_right.x;
		frustum->right.y = frustum->near_right.y;
	}
	else
	{
		frustum->left.x = (frustum->far_left.x - frustum->near_left.x)
			/ sample_height + frustum->near_left.x;
		frustum->left.y = (frustum->far_left.y - frustum->near_left.y)
			/ sample_height + frustum->near_left.y;
		frustum->right.x = (frustum->far_right.x - frustum->near_right.x)
			/ sample_height + frustum->near_right.x;
		frustum->right.y = (frustum->far_right.y - frustum->near_right.y)
			/ sample_height + frustum->near_right.y;
	}
}

static int	get_floor_color(t_cub3d *cub3d, t_frustum *frustum, int x)
{
	double		sample_width;
	t_dvector	d_sample;
	t_vector	sample;
	int			color;

	sample_width = (double)x / (double)cub3d->img->width;
	d_sample.x = (frustum->right.x - frustum->left.x)
		* sample_width + frustum->left.x;
	d_sample.y = (frustum->right.y - frustum->left.y)
		* sample_width + frustum->left.y;
	sample.x = floor(d_sample.x);
	sample.y = floor(d_sample.y);
	sample.x = sample.x % cub3d->floor.texture->width;
	sample.y = sample.y % cub3d->floor.texture->height;
	color = get_pixel_color(cub3d->floor, sample);
	return (color);
}

void	draw_floor(t_cub3d *cub3d, t_frustum *frustum)
{
	int	y;
	int	x;
	int	color;

	set_frustum(cub3d, frustum);
	y = -1;
	while (++y < (int)cub3d->img->height / 2)
	{
		set_frustum_vectors(cub3d, frustum, y);
		x = -1;
		while (++x < (int)cub3d->img->width)
		{
			color = get_floor_color(cub3d, frustum, x);
			mlx_put_pixel(cub3d->img, x, y + cub3d->img->height / 2, color);
			mlx_put_pixel(cub3d->img, x, cub3d->img->height / 2 - y, color);
		}
	}
	draw_horizon(cub3d);
}
