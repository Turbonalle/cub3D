/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:45:43 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 21:22:27 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	set_cursor_corners(triangle_t *triangle,
	dvector_t rotating_point,
	double angle_from_player_direction)
{
	triangle->a.x = (int)(rotating_point.x + triangle->height
			* cos(to_radians(angle_from_player_direction)));
	triangle->a.y = (int)(rotating_point.y + triangle->height
			* sin(to_radians(angle_from_player_direction)));
	triangle->b.x = (int)(rotating_point.x + triangle->base / 2
			* cos(to_radians(within_360(angle_from_player_direction - 90))));
	triangle->b.y = (int)(rotating_point.y + triangle->base / 2
			* sin(to_radians(within_360(angle_from_player_direction - 90))));
	triangle->c.x = (int)(rotating_point.x + triangle->base / 2
			* cos(to_radians(within_360(angle_from_player_direction + 90))));
	triangle->c.y = (int)(rotating_point.y + triangle->base / 2
			* sin(to_radians(within_360(angle_from_player_direction + 90))));
}

static double	get_angle_from_player_direction(cub3d_t *cub3d,
	double angle_from_player)
{
	double	res;
	range_t	angle_range_to;
	range_t	angle_range_from;

	res = within_360(angle_from_player - cub3d->player.angle * 180 / M_PI);
	angle_range_to.start = 90;
	angle_range_to.end = 270;
	angle_range_from.start = cub3d->fov / 2;
	angle_range_from.end = 360 - cub3d->fov / 2;
	res = lerp(angle_range_to, angle_range_from, res);
	return (res);
}

static int	get_triangle_height(double triangle_height)
{
	range_t	height_to;
	range_t	height_from;
	int		res;

	height_to.start = ENEMY_CURSOR_MIN_HEIGHT;
	height_to.end = ENEMY_CURSOR_MAX_HEIGHT;
	height_from.start = 0;
	height_from.end = ENEMY_CURSOR_MAX_HEIGHT;
	res = lerp(height_to, height_from, triangle_height);
	return (res);
}

void	enemy_cursor(cub3d_t *cub3d, double angle_from_player, double distance)
{
	dvector_t	rotating_point;
	triangle_t	triangle;
	double		angle_from_player_direction;

	if (distance <= 0)
		return ;
	angle_from_player_direction = get_angle_from_player_direction(cub3d,
			angle_from_player);
	set_enemy_cursor_position(cub3d, angle_from_player_direction,
		&rotating_point);
	angle_from_player_direction = within_360(angle_from_player_direction - 90);
	triangle.height = ENEMY_CURSOR_MAX_HEIGHT / distance;
	triangle.height = get_triangle_height(triangle.height);
	triangle.base = triangle.height * 3;
	set_cursor_corners(&triangle, rotating_point, angle_from_player_direction);
	draw_filled_triangle(cub3d->img, &triangle, ENEMY_CURSOR_COLOR);
}
