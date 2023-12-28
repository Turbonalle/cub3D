#include "../incl/cub3d.h"

// void	get_enemy_cursor_position(cub3d_t *cub3d, double angle_from_player, dvector_t *position)
// {
	
// }

void	enemy_cursor(cub3d_t *cub3d, double angle_from_player, double distance)
{
	int			height;
	int			base;
	dvector_t	rotating_point;
	triangle_t	triangle;
	double		angle_from_player_direction;

	angle_from_player_direction = within_360(angle_from_player - cub3d->player.angle * 180 / M_PI);
	angle_from_player_direction = lerp(90, 270, cub3d->fov / 2, 360 - cub3d->fov / 2, angle_from_player_direction);
	angle_from_player_direction = within_360(angle_from_player_direction - 90);
	if (distance <= 0)
		return ;
	height = MAX_TRIANGLE_HEIGHT / distance;
	base = height * 3;
	rotating_point.x = cub3d->img->width / 2;
	rotating_point.y = cub3d->img->height / 2;
	// get_enemy_cursor_position(cub3d, angle_from_player_direction, &rotating_point);
	triangle.a.x = (int)(rotating_point.x + height * cos(to_radians(angle_from_player_direction)));
	triangle.a.y = (int)(rotating_point.y + height * sin(to_radians(angle_from_player_direction)));
	triangle.b.x = (int)(rotating_point.x + base / 2 * cos(to_radians(within_360(angle_from_player_direction - 90))));
	triangle.b.y = (int)(rotating_point.y + base / 2 * sin(to_radians(within_360(angle_from_player_direction - 90))));
	triangle.c.x = (int)(rotating_point.x + base / 2 * cos(to_radians(within_360(angle_from_player_direction + 90))));
	triangle.c.y = (int)(rotating_point.y + base / 2 * sin(to_radians(within_360(angle_from_player_direction + 90))));
	draw_filled_triangle(cub3d->img, &triangle, GRAY_DARK);
}
