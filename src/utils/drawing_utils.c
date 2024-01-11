#include "../incl/cub3d.h"

void	draw_square(mlx_image_t *img, vector_t coord, int size, int color)
{
	vector_t	end;
	int			x;

	end.x = coord.x + size;
	end.y = coord.y + size;
	x = coord.x;
	while (coord.y < end.y)
	{
		coord.x = x;
		while (coord.x < end.x)
		{
			mlx_put_pixel(img, coord.x, coord.y, color);
			coord.x++;
		}
		coord.y++;
	}
}

void draw_horizontal_line(mlx_image_t *img, int x1, int x2, int y, int color)
{
	while (x1 <= x2)
	{
		mlx_put_pixel(img, x1, y, color);
		x1++;
	}
}

void	draw_circle(mlx_image_t *img, vector_t pos, int radius, int color)
{
	vector_t	center;
	int			x;
	int			y;
	int			decision;

	center.x = pos.x + radius;
	center.y = pos.y + radius;
	x = radius;
	y = 0;
	decision = 1 - radius;
	while (x >= y)
	{
		draw_horizontal_line(img, center.x - x, center.x + x, center.y + y, color);
		draw_horizontal_line(img, center.x - x, center.x + x, center.y - y, color);
		draw_horizontal_line(img, center.x - y, center.x + y, center.y + x, color);
		draw_horizontal_line(img, center.x - y, center.x + y, center.y - x, color);
		y++;
		if (decision <= 0)
			decision += 2 * y + 1;
		else
		{
			x--;
			decision += 2 * (y - x) + 1;
		}
	}
}
