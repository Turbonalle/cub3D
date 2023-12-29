#include "../incl/cub3d.h"

void	cursor_right_side(cub3d_t *cub3d,
	double cursor_angle,
	dvector_t *position)
{
	double	theta;

	theta = 180 - cursor_angle;
	position->x = cub3d->img->width / 2 + tan(to_radians(theta))
		* (cub3d->img->height / 2 - ENEMY_CURSOR_MARGIN);
	position->y = cub3d->img->height - ENEMY_CURSOR_MARGIN;
	if (position->x > cub3d->img->width - ENEMY_CURSOR_MARGIN)
	{
		theta = cursor_angle - 90;
		position->x = cub3d->img->width - ENEMY_CURSOR_MARGIN;
		position->y = cub3d->img->height / 2 + tan(to_radians(theta))
			* (cub3d->img->width / 2 - ENEMY_CURSOR_MARGIN);
	}
}

void	cursor_left_side(cub3d_t *cub3d,
	double cursor_angle,
	dvector_t *position)
{
	double	theta;

	theta = cursor_angle - 180;
	position->x = cub3d->img->width / 2 - tan(to_radians(theta))
		* (cub3d->img->height / 2 - ENEMY_CURSOR_MARGIN);
	position->y = cub3d->img->height - ENEMY_CURSOR_MARGIN;
	if (position->x < ENEMY_CURSOR_MARGIN)
	{
		theta = 270 - cursor_angle;
		position->x = ENEMY_CURSOR_MARGIN;
		position->y = cub3d->img->height / 2 + tan(to_radians(theta))
			* (cub3d->img->width / 2 - ENEMY_CURSOR_MARGIN);
	}
}

void	set_enemy_cursor_position(cub3d_t *cub3d,
	double cursor_angle,
	dvector_t *position)
{
	if (cursor_angle <= 180)
		cursor_right_side(cub3d, cursor_angle, position);
	else
		cursor_left_side(cub3d, cursor_angle, position);
}

void	set_cursor_corners(triangle_t *triangle,
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

void	enemy_cursor(cub3d_t *cub3d, double angle_from_player, double distance)
{
	dvector_t	rotating_point;
	triangle_t	triangle;
	double		angle_from_player_direction;

	if (distance <= 0)
		return ;
	angle_from_player_direction = within_360(angle_from_player
			- cub3d->player.angle * 180 / M_PI);
	angle_from_player_direction = lerp(90, 270, cub3d->fov / 2,
			360 - cub3d->fov / 2, angle_from_player_direction);
	set_enemy_cursor_position(cub3d, angle_from_player_direction,
		&rotating_point);
	angle_from_player_direction = within_360(angle_from_player_direction - 90);
	triangle.height = ENEMY_CURSOR_MAX_HEIGHT / distance;
	if (triangle.height > ENEMY_CURSOR_MAX_HEIGHT)
		triangle.height = ENEMY_CURSOR_MAX_HEIGHT;
	triangle.height = lerp(ENEMY_CURSOR_MIN_HEIGHT, ENEMY_CURSOR_MAX_HEIGHT, 0,
			ENEMY_CURSOR_MAX_HEIGHT, triangle.height);
	triangle.base = triangle.height * 3;
	set_cursor_corners(&triangle, rotating_point, angle_from_player_direction);
	draw_filled_triangle(cub3d->img, &triangle, ENEMY_CURSOR_COLOR);
}
