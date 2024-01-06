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

//------------------------------------------------------------------------------

void	draw_button(mlx_image_t *img, button_t *button)
{
	int	row;
	int	column;

	row = button->pos.y;
	while (row < button->pos.y + button->height)
	{
		column = button->pos.x;
		while (column < button->pos.x + button->width)
		{
			if (row < button->pos.y + button->border_width
				|| row >= button->pos.y + button->height - button->border_width
				|| column < button->pos.x + button->border_width
				|| column >= button->pos.x + button->width - button->border_width)
				mlx_put_pixel(img, column, row, button->border_color);
			else
				mlx_put_pixel(img, column, row, button->background_color);
			column++;
		}
		row++;
	}
}