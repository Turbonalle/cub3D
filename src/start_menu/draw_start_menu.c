#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void	draw_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{
	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create pause menu image");

	draw_menu_background(menu->img, menu->background_color);
	draw_rectangle(menu->img, &menu->rect_title);
	draw_button(menu->img, &menu->button_start);
	draw_button(menu->img, &menu->button_level);
	draw_button(menu->img, &menu->button_settings);
	draw_button(menu->img, &menu->button_exit);

	mlx_image_to_window(cub3d->mlx, menu->img, 0, 0);
	menu->text_title = mlx_put_string(cub3d->mlx, "Cub3D", menu->rect_title.pos.x + menu->rect_title.width * 0.5, menu->rect_title.pos.y + menu->rect_title.height * 0.5);
	center(menu->text_title);
	menu->text_start = mlx_put_string(cub3d->mlx, "Start", menu->button_start.pos.x + menu->button_start.width * 0.5, menu->button_start.pos.y + menu->button_start.height * 0.5);
	center(menu->text_start);
	menu->text_level = mlx_put_string(cub3d->mlx, "Level", menu->button_level.pos.x + menu->button_level.width * 0.5, menu->button_level.pos.y + menu->button_level.height * 0.5);
	center(menu->text_level);
	menu->text_settings = mlx_put_string(cub3d->mlx, "Settings", menu->button_settings.pos.x + menu->button_settings.width * 0.5, menu->button_settings.pos.y + menu->button_settings.height * 0.5);
	center(menu->text_settings);
	menu->text_exit = mlx_put_string(cub3d->mlx, "Exit", menu->button_exit.pos.x + menu->button_exit.width * 0.5, menu->button_exit.pos.y + menu->button_exit.height * 0.5);
	center(menu->text_exit);
}
