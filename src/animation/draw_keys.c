/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:02:35 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/15 21:42:39 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	position_key(key_node_t *key, mlx_texture_t *texture, double factor)
{
	key->img_curr_frame->instances[0].x
		= key->pos_screen.x - texture->width * factor * 0.5;
	key->img_curr_frame->instances[0].y
		= key->pos_screen.y - texture->height * factor * 1.5;
}

static void	scale_key(cub3d_t *cub3d, key_node_t *key, mlx_texture_t *texture,
	double factor)
{
	uvector_t	src;
	uvector_t	res;
	int			ray;

	empty_image(key->img_curr_frame);
	res.row = 0;
	while (res.row++ < texture->height * factor)
	{
		res.col = 0;
		if (res.row < key->img_curr_frame->height)
		{
			while (res.col++ < texture->width * factor)
			{
				if (res.col < key->img_curr_frame->width)
				{
					set_src_coordinates(&src, res, factor, texture);
					ray = get_ray_i(key->pos_screen.x, texture, factor, res);
					if (column_visible(cub3d, key->dist_to_player, ray))
						copy_pixel(key->img_curr_frame, res, texture, src);
				}
			}
		}
	}
	position_key(key, texture, factor);
}

static void	draw_keys(cub3d_t *cub3d, int group_index, int curr_frame_num)
{
	key_node_t	*tmp;
	double		scale_factor;

	tmp = cub3d->level->key_groups[group_index].keys;
	while (tmp)
	{
		if (tmp->collected == FALSE && tmp->visible == TRUE)
		{
			tmp->img_curr_frame->instances[0].enabled = TRUE;
			scale_factor = calculate_scale_factor(tmp->dist_to_player,
					KEY_NORMAL_SCALE_DISTANCE);
			scale_key(
				cub3d,
				tmp,
				cub3d->level->key_groups[group_index]
				.textures_frames[curr_frame_num],
				scale_factor);
		}
		else if (tmp->visible == FALSE || tmp->collected == TRUE)
		{
			tmp->img_curr_frame->instances[0].enabled = FALSE;
		}
		tmp = tmp->next;
	}
}

void	draw_all_keys(cub3d_t *cub3d)
{
	int	i;

	i = 0;
	while (i < NUM_DOORS_MAX)
	{
		if (cub3d->level->door_groups[i].num_keys_left > 0)
			draw_keys(cub3d, i, cub3d->level->key_groups[i].curr_frame_index);
		i++;
	}
}
