/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:31 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/16 10:11:22 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	scale_enemy(cub3d_t *cub3d, t_enemy *enemy, mlx_texture_t *src, double factor)
{
	uint32_t	row_src;
	uint32_t	col_src;
	uint32_t	row_res;
	uint32_t	col_res;
	int			ray_index;

	enemy->img_curr_frame->instances[0].enabled = TRUE;
	ft_memset(enemy->img_curr_frame->pixels, 0, enemy->img_curr_frame->width * enemy->img_curr_frame->height * 4);
	row_res = 0;
	while (row_res < src->height * factor)
	{
		col_res = 0;
		if (row_res < enemy->img_curr_frame->height)
		{
			while (col_res < src->width * factor)
			{
				if (col_res < enemy->img_curr_frame->width)
				{
					row_src = (uint32_t)round(row_res / factor);
					if (row_src >= src->height)
						row_src--;
					col_src = (uint32_t)round(col_res / factor);
					if (col_src >= src->width)
						col_src--;
					ray_index = (int)(enemy->pos_screen.x - src->width * factor * 0.5 + col_res);
					if (ray_index >= 0 && ray_index < WIDTH && cub3d->rays[ray_index].length > enemy->dist_to_player)
						ft_memcpy(enemy->img_curr_frame->pixels + row_res * enemy->img_curr_frame->width * 4 + col_res * 4,
							src->pixels + row_src * src->width * 4 + col_src * 4,
							4);
				}
				col_res++;
			}
		}
		row_res++;
	}
	enemy->img_curr_frame->instances[0].x = enemy->pos_screen.x - src->width * factor * 0.5;
	enemy->img_curr_frame->instances[0].y = enemy->pos_screen.y - src->height * factor;
}

static void	draw_enemy_frame(cub3d_t *cub3d, t_enemy *enemy)
{
	double			scale_factor;
	mlx_texture_t	*frame;
	int				enemy_dir;

	scale_factor = calculate_scale_factor(enemy->dist_to_player,
			ENEMY_NORMAL_SCALE_DISTANCE);
	enemy_dir = get_enemy_dir(enemy);
	// if (enemy->state == HUNTING)
	// 	frame = cub3d->frames_hunt[enemy_dir][cub3d->curr_frame_index_hunt];
	if (enemy->state == IDLE)
		frame = cub3d->frames_idle[enemy_dir][cub3d->curr_frame_index_idle];
	else
		frame
			= cub3d->frames_walking[enemy_dir][cub3d->curr_frame_index_walking];
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
