/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_line_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:50:05 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/18 09:53:43 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	find_wall_texture(t_cub3d *cub3d, t_ray ray, t_texture *texture)
{
	if (ray.wall == NO)
		*texture = cub3d->level->texture[0];
	if (ray.wall == SO)
		*texture = cub3d->level->texture[1];
	if (ray.wall == WE)
		*texture = cub3d->level->texture[2];
	if (ray.wall == EA)
		*texture = cub3d->level->texture[3];
}

t_texture	find_texture(t_cub3d *cub3d, t_ray ray)
{
	t_texture	texture;
	int			frame_index;

	find_wall_texture(cub3d, ray, &texture);
	if (ray.wall == 'A')
		texture = cub3d->door[0];
	if (ray.wall == 'B')
		texture = cub3d->door[1];
	if (ray.wall == 'C')
		texture = cub3d->door[2];
	if (ray.wall == 'D')
		texture = cub3d->door[3];
	if (ray.wall == 'O')
		texture = cub3d->door[4];
	if (ray.wall == 'G')
	{
		frame_index = (int)(cub3d->run_time
				/ ANIMATION_INTERVAL_MS * 500) % NUM_FRAMES_STARS;
		texture = cub3d->stars[frame_index];
	}
	return (texture);
}
