/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:32:11 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

double	paused_time(t_cub3d *cub3d)
{
	return (mlx_get_time() - cub3d->pause_timestamp);
}

void	pause_timer(t_cub3d *cub3d)
{
	cub3d->pause_timestamp = mlx_get_time();
}

void	continue_timer(t_cub3d *cub3d)
{
	cub3d->start_timestamp += paused_time(cub3d);
	cub3d->frame_start_timestamp = cub3d->start_timestamp;
}

void	free_three_strs(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

void	draw_timer(t_cub3d *cub3d)
{
	update_timer(cub3d);
	mlx_delete_image(cub3d->mlx, cub3d->timer.img_time);
	cub3d->timer.img_time = mlx_put_string(cub3d->mlx, cub3d->timer.text_time,
			cub3d->timer.pos.x, cub3d->timer.pos.y);
	cub3d->timer.img_time->instances[0].x -= cub3d->timer.img_time->width;
	free(cub3d->timer.text_time);
}
