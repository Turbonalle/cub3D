#include "../incl/cub3d.h"

void	draw_background(mlx_image_t *img, int color)
{
	unsigned int	row;
	unsigned int	column;

	row = -1;
	while (++row < img->height)
	{
		column = -1;
		while (++column < img->width)
		{
			mlx_put_pixel(img, column, row, color);
		}
	}
}
