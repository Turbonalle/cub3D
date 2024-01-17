/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:31 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 00:15:11 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	position_enemy(t_enemy *enemy, mlx_texture_t *texture,
	double factor)
{
	enemy->img_curr_frame->instances[0].x
		= enemy->pos_screen.x - texture->width * factor * 0.5;
	enemy->img_curr_frame->instances[0].y
		= enemy->pos_screen.y - texture->height * factor;
}

static void	scale_enemy(cub3d_t *cub3d, t_enemy *enemy, mlx_texture_t *texture,
	double factor)
{
	uvector_t	src;
	uvector_t	res;
	int			ray;

	enemy->img_curr_frame->instances[0].enabled = TRUE;
	empty_image(enemy->img_curr_frame);
	res.row = 0;
	while (res.row++ < texture->height * factor)
	{
		res.col = 0;
		if (res.row < enemy->img_curr_frame->height)
		{
			while (res.col++ < texture->width * factor)
			{
				if (res.col < enemy->img_curr_frame->width)
				{
					set_src_coordinates(&src, res, factor, texture);
					ray = get_ray_i(enemy->pos_screen.x, texture, factor, res);
					if (column_visible(cub3d, enemy->dist_to_player, ray))
						copy_pixel(enemy->img_curr_frame, res, texture, src);
				}
			}
		}
	}
	position_enemy(enemy, texture, factor);
}

static void	draw_enemy_frame(cub3d_t *cub3d, t_enemy *enemy)
{
	double			scale_factor;
	mlx_texture_t	*frame;
	int				enemy_dir;

	scale_factor = calculate_scale_factor(enemy->dist_to_player,
			ENEMY_NORMAL_SCALE_DISTANCE);
	enemy_dir = get_enemy_dir(enemy);
	if (enemy->state == HUNTING)
		frame
			= cub3d->frames_hunting[enemy_dir][cub3d->curr_frame_index_hunting];
	else if (enemy->state == WALKING)
		frame
			= cub3d->frames_walking[enemy_dir][cub3d->curr_frame_index_walking];
	else
		frame = cub3d->frames_idle[enemy_dir][cub3d->curr_frame_index_idle];
	scale_enemy(
		cub3d,
		enemy,
		frame,
		scale_factor);
}

void	draw_all_enemies(cub3d_t *cub3d, t_enemy **enemies)
{
	int	i;

	i = 0;
	while (enemies[i])
	{
		draw_enemy_frame(cub3d, enemies[i]);
		i++;
	}
}
