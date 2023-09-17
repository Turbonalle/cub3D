#include "../incl/raycaster.h"

//------------------------------------------------------------------------------

void draw_background(mlx_image_t *img, int color)
{
	int x;
	int y;

	x = -1;
	while (++x < (int)img->width)
	{
		y = -1;
		while (++y < (int)img->height)
			mlx_put_pixel(img, x, y, color);
	}
}

//------------------------------------------------------------------------------

void draw_vertical_line(mlx_image_t *img, int color, int x, int start, int end)
{
	int y;

	// printf("Drawing vertical line...\n");
	if (start > end)
		switch_values(&start, &end);
	y = start;
	while (y < end)
	{
		// printf("[x, y, color] = [%d, %d, %d]\n", x, y, color);
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void draw_horizontal_line(mlx_image_t *img, int color, int y, int start, int end)
{
	int x;

	// printf("Drawing horizontal line...\n");
	if (start > end)
		switch_values(&start, &end);
	x = start;
	while (x < end)
	{
		// printf("[x, y, color] = [%d, %d, %d]\n", x, y, color);
		mlx_put_pixel(img, x, y, color);
		x++;
	}
}

//------------------------------------------------------------------------------

void draw_grid_fixed_size(mlx_image_t *img, int color, int size)
{
	int x;
	int y;

	// printf("Drawing grid...\n");
	x = size;
	while (x < (int)img->width)
	{
		draw_vertical_line(img, color, x, 0, (int)img->height);
		x += size;
	}
	y = size;
	while (y < (int)img->height)
	{
		draw_horizontal_line(img, color, y, 0, (int)img->width);
		y += size;
	}
}

//------------------------------------------------------------------------------

void draw_border(mlx_image_t *img, int color)
{
	draw_vertical_line(img, color, 0, 0, (int)img->height);
	draw_vertical_line(img, color, (int)img->height - 1, 0, (int)img->height);
	draw_horizontal_line(img, color, 0, 0, (int)img->width);
	draw_horizontal_line(img, color, (int)img->width - 1, 0, (int)img->width);
}

//------------------------------------------------------------------------------

void draw_grid_relative_size(mlx_image_t *img, int color, int columns, int rows)
{
	int x;
	int y;
	int i;

	if (columns == 0 || rows == 0)
	{
		printf("Can't divide by zero!n");
		return ;
	}
	// printf("Drawing grid...\n");
	i = 1;
	x = ((int)img->width - (BORDER_THICKNESS * 2)) * i / columns;
	while (x < (int)img->width)
	{
		draw_vertical_line(img, color, x, 0, (int)img->height);
		i++;
		x = ((int)img->width - (BORDER_THICKNESS * 2)) * i / columns;
	}
	i = 1;
	y = ((int)img->height - (BORDER_THICKNESS * 2)) * i / columns;
	while (y < (int)img->height)
	{
		draw_horizontal_line(img, color, y, 0, (int)img->width);
		i++;
		y = ((int)img->height - (BORDER_THICKNESS * 2)) * i / columns;
	}
	draw_border(img, color);
}