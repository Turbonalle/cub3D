#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void	init_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{
	float	title_rect_width_percentage;
	float	title_rect_height_percentage;

	// set title
	title_rect_width_percentage = 0.5;
	title_rect_height_percentage = 0.5;
	menu->rect_title.width = cub3d->img->width * title_rect_width_percentage;
	menu->rect_title.height = cub3d->img->height * title_rect_height_percentage;
	menu->rect_title.pos.x = (cub3d->img->width - menu->rect_title.width) / 2;
	menu->rect_title.pos.y = cub3d->img->height * 0.1;
	
	// set buttons
	menu->button_start.width = menu->rect_title.width * 0.5;
	menu->button_start.height = menu->button_start.width * 0.3;
	menu->button_start.pos.x = menu->rect_title.pos.x + menu->rect_title.width * 0.25;
	menu->button_start.pos.y = cub3d->img->height * 0.6;
	menu->button_settings.width = menu->rect_title.width * 0.5;
	menu->button_settings.height = menu->button_settings.width * 0.3;
	menu->button_settings.pos.x = menu->rect_title.pos.x + menu->rect_title.width * 0.25;
	menu->button_settings.pos.y = cub3d->img->height * 0.7;

	// set background color
	menu->background_color = BLACK;
}
