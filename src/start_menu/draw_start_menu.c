#include "../incl/cub3d.h"

void	draw_start_menu_background(cub3d_t *cub3d, start_menu_t *menu)
{
	unsigned int	row;
	unsigned int	column;

	row = -1;
	while (++row < cub3d->img->height)
	{
		column = -1;
		while (++column < cub3d->img->width)
		{
			if (row < cub3d->img->height / 2)
				mlx_put_pixel(menu->img, column, row, menu->background_color);
			else
				mlx_put_pixel(menu->img, column, row, menu->background_color);
		}
	}
}

//------------------------------------------------------------------------------

void	draw_button(cub3d_t *cub3d, button_t *button)
{
	int	row;
	int	column;

	row = button->pos.y;
	while (row < button->pos.y + button->height)
	{
		column = button->pos.x;
		while (column < button->pos.x + button->width)
		{
			mlx_put_pixel(cub3d->start_menu.img, column, row, button->background_color);
			column++;
		}
		row++;
	}
}

//------------------------------------------------------------------------------

void	draw_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{
	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create pause menu image");

	draw_start_menu_background(cub3d, menu);
	draw_button(cub3d, &menu->button_start);
	draw_button(cub3d, &menu->button_settings);

	mlx_image_to_window(cub3d->mlx, menu->img, 0, 0);
	menu->text_title = mlx_put_string(cub3d->mlx, "Cub3D", menu->rect_title.pos.x + menu->rect_title.width * 0.5, menu->rect_title.pos.y + menu->rect_title.height * 0.1);
	center(menu->text_title);
	menu->text_start = mlx_put_string(cub3d->mlx, "Start", menu->button_start.pos.x + menu->button_start.width * 0.5, menu->button_start.pos.y + menu->button_start.height * 0.1);
	center(menu->text_start);
	menu->text_settings = mlx_put_string(cub3d->mlx, "Settings", menu->button_settings.pos.x + menu->button_settings.width * 0.5, menu->button_settings.pos.y + menu->button_settings.height * 0.1);
	center(menu->text_settings);
}
