#include "../incl/cub3d.h"

void	draw_rectangle(mlx_image_t *img, rectangle_t *rect)
{
	int	row;
	int	column;

	row = rect->pos.y;
	while (++row < rect->pos.y + rect->height)
	{
		column = rect->pos.x;
		//printf("draw_rectangle: row: %d, column: %d\n", row, column);
		while (++column < rect->pos.x + rect->width)
		{
			/* if (column < 0 || column >= (int)img->width || row < 0 || row >= (int)img->height)
			{
				printf("ERROR: rectangle out of bounds\n");
				printf("rect->pos.x: %d, rect->pos.y: %d\n", rect->pos.x, rect->pos.y);
				printf("rect->width: %d, rect->height: %d\n", rect->width, rect->height);
				printf("row: %d, column: %d\n", row, column);
			} */
			mlx_put_pixel(img, column, row, rect->color);
		}
	}
}

void	draw_checkbox(cub3d_t *cub3d, box_t *box)
{
	int	row;
	int	column;

	if (box->state == TRUE)
		box->background_color = BOX_ON_COLOR;
	else
		box->background_color = BOX_OFF_COLOR;
	row = box->pos.y;
	while (++row < box->pos.y + box->size)
	{
		column = box->pos.x;
		while (++column < box->pos.x + box->size)
		{
			if (row < box->pos.y + box->border_width || row > box->pos.y + box->size - box->border_width)
				mlx_put_pixel(cub3d->pause_menu.img, column, row, box->border_color);
			else if (column < box->pos.x + box->border_width || column > box->pos.x + box->size - box->border_width)
				mlx_put_pixel(cub3d->pause_menu.img, column, row, box->border_color);
			else
				mlx_put_pixel(cub3d->pause_menu.img, column, row, box->background_color);
		}
	}
}

void	draw_hovered_checkbox(cub3d_t *cub3d, box_t *box)
{
	int	row;
	int	column;

	if (box->state == TRUE)
		box->background_color = BOX_HOVER_ON_COLOR;
	else
		box->background_color = BOX_HOVER_OFF_COLOR;
	row = box->pos.y;
	while (++row < box->pos.y + box->size)
	{
		column = box->pos.x;
		while (++column < box->pos.x + box->size)
		{
			if (row < box->pos.y + box->border_width || row > box->pos.y + box->size - box->border_width)
				mlx_put_pixel(cub3d->pause_menu.img, column, row, box->border_color);
			else if (column < box->pos.x + box->border_width || column > box->pos.x + box->size - box->border_width)
				mlx_put_pixel(cub3d->pause_menu.img, column, row, box->border_color);
			else
				mlx_put_pixel(cub3d->pause_menu.img, column, row, box->background_color);
		}
	}
}