#include "../incl/cub3d.h"

void draw_rectangle(cub3d_t *cub3d, rectangle_t *rect)
{
	int	row;
	int	column;

	row = rect->pos.y;
	while (++row < rect->pos.y + rect->height)
	{
		column = rect->pos.x;
		while (++column < rect->pos.x + rect->width)
			mlx_put_pixel(cub3d->pause_menu.img, column, row, rect->color);
	}
}

void draw_checkbox(cub3d_t *cub3d, box_t *box)
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

void draw_hovered_checkbox(cub3d_t *cub3d, box_t *box)
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