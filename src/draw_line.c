#include "../incl/cub3d.h"

void draw_line(mlx_image_t *img, dvector_t start, dvector_t end, int color)
{
	double x;
	double y;
	double x_increment;
	double y_increment;
	int i;
	int iterations = 600;

	x = start.x;
	y = start.y;
	x_increment = (end.x - start.x) / iterations;
	y_increment = (end.y - start.y) / iterations;
	i = 0;
	while (i < iterations)
	{
		x += x_increment;
		y += y_increment;
		mlx_put_pixel(img, x, y, color);
		i++;
	}
}