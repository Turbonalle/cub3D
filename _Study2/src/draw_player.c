#include "../incl/raycaster.h"

void draw_player(cub3d_t *cub3d)
{
	int radius = 10;
	vector_t pixel;

	pixel.x = cub3d->player.pos.x - radius;
	while (pixel.x < cub3d->player.pos.x + radius)
	{
		pixel.y = cub3d->player.pos.y - radius;
		while (pixel.y < cub3d->player.pos.y + radius)
		{
			if (distance(pixel, cub3d->player.pos) <= (double)radius)
				mlx_put_pixel(cub3d->img, pixel.x, pixel.y, RED);
			pixel.y++;
		}
		pixel.x++;
	}
}