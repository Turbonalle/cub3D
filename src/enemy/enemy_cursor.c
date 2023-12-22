#include "../incl/cub3d.h"

# define MAX_TRIANGLE_HEIGHT 150

typedef struct triangle_s
{
	dvector_t	a;
	dvector_t	b;
	dvector_t	c;
} 				triangle_t;

void	draw_triangle(cub3d_t *cub3d, triangle_t triangle, int color)
{
	draw_line(cub3d->img, triangle.a, triangle.b, color);
	draw_line(cub3d->img, triangle.b, triangle.c, color);
	draw_line(cub3d->img, triangle.c, triangle.a, color);
}

void	enemy_cursor(cub3d_t *cub3d, double angle_from_player, double distance)
{
	int	height;
	int	base;
	dvector_t	rotating_point;
	triangle_t	triangle;

	if (distance <= 0)
		return ;
	height = MAX_TRIANGLE_HEIGHT / distance;
	base = height * 3;
	rotating_point.x = cub3d->img->width / 2;
	rotating_point.y = cub3d->img->height / 2;
	triangle.a.x = rotating_point.x + height * cos(to_radians(angle_from_player));
	triangle.a.y = rotating_point.y + height * sin(to_radians(angle_from_player));
	triangle.b.x = rotating_point.x + base / 2 * cos(to_radians(within_360(angle_from_player - 90)));
	triangle.b.y = rotating_point.y + base / 2 * sin(to_radians(within_360(angle_from_player - 90)));
	triangle.c.x = rotating_point.x + base / 2 * cos(to_radians(within_360(angle_from_player + 90)));
	triangle.c.y = rotating_point.y + base / 2 * sin(to_radians(within_360(angle_from_player + 90)));
	draw_triangle(cub3d, triangle, RED);
}