#include "../incl/cub3d.h"

static void	draw_top_border(mlx_image_t *img)
{
	unsigned int	row;
	unsigned int	col;

	row = -1;
	while (++row < MENU_BORDER_THICKNESS)
	{
		col = -1;
		while (++col < img->width)
		{
			if (col > row && col < img->width - row - 1)
				mlx_put_pixel(img, col, row, MENU_BORDER_TOP_COLOR);
			else if (col == row)
				mlx_put_pixel(img, col, row, get_color_mix(MENU_BORDER_TOP_COLOR, MENU_BORDER_LEFT_COLOR));
			else if (col == img->width - row - 1)
				mlx_put_pixel(img, col, row, get_color_mix(MENU_BORDER_TOP_COLOR, MENU_BORDER_RIGHT_COLOR));
		}
	}
}

static void	draw_bottom_border(mlx_image_t *img)
{
	unsigned int	row;
	unsigned int	col;

	row = img->height - MENU_BORDER_THICKNESS;
	while (row < img->height)
	{
		col = -1;
		while (++col < img->width)
		{
			if (col > img->height - row - 1 && img->width - col > img->height - row)
				mlx_put_pixel(img, col, row, MENU_BORDER_BOTTOM_COLOR);
			else if (col == img->height - row - 1)
				mlx_put_pixel(img, col, row, get_color_mix(MENU_BORDER_BOTTOM_COLOR, MENU_BORDER_LEFT_COLOR));
			else if (img->width - col == img->height - row)
				mlx_put_pixel(img, col, row, get_color_mix(MENU_BORDER_BOTTOM_COLOR, MENU_BORDER_RIGHT_COLOR));
		}
		row++;
	}
}

static void draw_left_border(mlx_image_t *img)
{
	unsigned int	row;
	unsigned int	col;

	col = -1;
	while (++col < MENU_BORDER_THICKNESS)
	{
		row = -1;
		while (++row < img->height)
		{
			if (row > col && row < img->height - col - 1)
				mlx_put_pixel(img, col, row, MENU_BORDER_LEFT_COLOR);
			else if (row == col)
				mlx_put_pixel(img, col, row, get_color_mix(MENU_BORDER_LEFT_COLOR, MENU_BORDER_TOP_COLOR));
			else if (row == img->height - col - 1)
				mlx_put_pixel(img, col, row, get_color_mix(MENU_BORDER_LEFT_COLOR, MENU_BORDER_BOTTOM_COLOR));
		}
	}
}

static void draw_right_border(mlx_image_t *img)
{
	unsigned int	row;
	unsigned int	col;

	col = img->width - MENU_BORDER_THICKNESS;
	while (col < img->width)
	{
		row = -1;
		while (++row < img->height)
		{
			if (row > img->width - col - 1 && img->width - col < img->height - row)
				mlx_put_pixel(img, col, row, MENU_BORDER_RIGHT_COLOR);
			else if (row == img->width - col - 1)
				mlx_put_pixel(img, col, row, get_color_mix(MENU_BORDER_RIGHT_COLOR, MENU_BORDER_TOP_COLOR));
			else if (img->width - col == img->height - row)
				mlx_put_pixel(img, col, row, get_color_mix(MENU_BORDER_RIGHT_COLOR, MENU_BORDER_BOTTOM_COLOR));
		}
		col++;
	}
}

void	draw_menu_border(mlx_image_t *img)
{
	draw_top_border(img);
	draw_bottom_border(img);
	draw_left_border(img);
	draw_right_border(img);
}
