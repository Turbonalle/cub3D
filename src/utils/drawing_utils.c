#include "../incl/cub3d.h"

void draw_square(cub3d_t *cub3d, int col, int row, int size, int color)
{
	
	vector_t end;
	int x;

	end.x = col + size;
	end.y = row + size;
	x = col;
	while (row < end.y)
	{
		col = x;
		while (col < end.x)
		{
			mlx_put_pixel(cub3d->minimap.img, col, row, color);
			col++;
		}
		row++;
	}
}

void mlx_draw_horizontal_line(mlx_image_t *img, int x1, int x2, int y, int color) {
	while (x1 <= x2)
	{
		mlx_put_pixel(img, x1, y, color);
		x1++;
	}
}

void draw_circle(mlx_image_t *img, int col, int row, int radius, int color) {
    vector_t center;
	int x;
    int y;
    int decision;

    center.x = col + radius;
    center.y = row + radius;
    x = radius;
    y = 0;
    decision = 1 - radius;
    
    while (x >= y) {
        mlx_draw_horizontal_line(img, center.x - x, center.x + x, center.y + y, color);
        mlx_draw_horizontal_line(img, center.x - x, center.x + x, center.y - y, color);
        mlx_draw_horizontal_line(img, center.x - y, center.x + y, center.y + x, color);
        mlx_draw_horizontal_line(img, center.x - y, center.x + y, center.y - x, color);
        y++;
        if (decision <= 0) {
            decision += 2 * y + 1;
        } else {
            x--;
            decision += 2 * (y - x) + 1;
        }
    }
}
