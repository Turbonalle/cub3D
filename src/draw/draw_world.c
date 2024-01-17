/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:16:00 by jbagger           #+#    #+#             */
/*   Updated: 2024/01/17 14:43:19 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static double	fisheye_correction(cub3d_t *cub3d,
	fisheye_t *fisheye,
	int index)
{
	fisheye->orto_dir.x = sin(cub3d->player.angle);
	fisheye->orto_dir.y = -cos(cub3d->player.angle);
	fisheye->ray.x = cub3d->rays[index].end.x - cub3d->player.pos.x;
	fisheye->ray.y = cub3d->rays[index].end.y - cub3d->player.pos.y;
	fisheye->proj_len = fisheye->orto_dir.x * fisheye->ray.x
		+ fisheye->orto_dir.y * fisheye->ray.y;
	fisheye->ray_proj.x = fisheye->proj_len * fisheye->orto_dir.x;
	fisheye->ray_proj.y = fisheye->proj_len * fisheye->orto_dir.y;
	fisheye->ray_perp.x = fisheye->ray.x - fisheye->ray_proj.x;
	fisheye->ray_perp.y = fisheye->ray.y - fisheye->ray_proj.y;
	fisheye->perp_dist = sqrt(fisheye->ray_perp.x * fisheye->ray_perp.x
			+ fisheye->ray_perp.y * fisheye->ray_perp.y);
	fisheye->view_fill_dist = WALL_HEIGHT / 2.0 / sin(to_radians(FOV / 2.0));
	fisheye->window_aspect_ratio = (double)cub3d->img->width
		/ (double)cub3d->img->height;
	return (cub3d->img->height * fisheye->view_fill_dist
		/ fisheye->perp_dist * fisheye->window_aspect_ratio);
}

static int	is_texture(char wall)
{
	return (wall == NO || wall == SO || wall == WE || wall == EA
		|| wall == 'A' || wall == 'B' || wall == 'C' || wall == 'D'
		|| wall == 'O' || wall == 'G');
}

static void	set_height(cub3d_t *cub3d, int index, double *height, int *close)
{
	*close = FALSE;
	if (cub3d->rays[index].length < 0)
		*height = cub3d->img->height;
	else if (cub3d->rays[index].length > 100)
		*height = 0;
	else
	{
		if (cub3d->settings.fisheye)
			*height = 1.0
				/ (M_PI * 2 * cub3d->rays[index].length * cub3d->fov / 360.0)
				* cub3d->img->width;
		else
			*height = fisheye_correction(cub3d, &cub3d->fisheye, index);
		if (*height > cub3d->img->height)
			*close = TRUE;
	}
}

static void	set_end(cub3d_t *cub3d, dvector_t *end, int index, double height)
{
	end->x = index;
	end->y = (cub3d->img->height + height) / 2;
	if (end->y == cub3d->img->height)
		end->y--;
}

void	draw_world(cub3d_t *cub3d)
{
	int			index;
	int			close;
	double		height;
	dvector_t	start;
	dvector_t	end;

	if (cub3d->draw_floor)
		draw_floor(cub3d, &cub3d->frustum);
	index = -1;
	while (++index < (int)cub3d->img->width)
	{
		set_height(cub3d, index, &height, &close);
		start.x = index;
		start.y = (cub3d->img->height - height) / 2;
		set_end(cub3d, &end, index, height);
		if (is_texture(cub3d->rays[index].wall))
		{
			if (close)
				draw_textured_line_close(cub3d, start, end, cub3d->rays[index]);
			else
				draw_textured_line(cub3d, start, end, cub3d->rays[index]);
		}
	}
}
