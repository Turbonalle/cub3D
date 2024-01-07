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
			if (row < img->height / 2)
				mlx_put_pixel(img, column, row, color);
			else
				mlx_put_pixel(img, column, row, color);
		}
	}
}
