#include "../incl/raycaster.h"

void draw_player(cub3d_t *cub3d)
{
	int radius = 10;
	double_vector_t pixel;

	pixel.x = (int)cub3d->player.pos.x - radius;
	while (pixel.x < (int)cub3d->player.pos.x + radius)
	{
		pixel.y = (int)cub3d->player.pos.y - radius;
		while (pixel.y < (int)cub3d->player.pos.y + radius)
		{
			if (distance(pixel, cub3d->player.pos) <= (double)radius)
				mlx_put_pixel(cub3d->img, pixel.x, pixel.y, RED);
			pixel.y++;
		}
		pixel.x++;
	}
}