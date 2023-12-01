#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void	init_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{
	float	title_rect_width_percentage;
	float	title_rect_height_percentage;
	float	space_between_buttons;

	// set variables in percentage to easily modify the menu
	title_rect_width_percentage = 0.5;
	title_rect_height_percentage = 0.5;
	space_between_buttons = 0.05;

	// set title
	menu->rect_title.width = cub3d->img->width * title_rect_width_percentage;
	menu->rect_title.height = cub3d->img->height * title_rect_height_percentage;
	menu->rect_title.pos.x = cub3d->img->width * 0.05;
	menu->rect_title.pos.y = cub3d->img->height * 0.1;
	
	// set start button
	menu->button_start.width = menu->rect_title.width * 0.5;
	menu->button_start.height = menu->button_start.width * 0.3;
	menu->button_start.pos.x = menu->rect_title.pos.x + menu->rect_title.width + (cub3d->img->width - (menu->rect_title.pos.x + menu->rect_title.width) - menu->button_start.width) / 2;
	menu->button_start.pos.y = menu->rect_title.pos.y;
	menu->button_start.background_color = BUTTON_COLOR;
	menu->button_start.border_color = BUTTON_BORDER_COLOR;
	menu->button_start.border_width = BUTTON_BORDER_THICKNESS;

	// set level button
	menu->button_level.width = menu->button_start.width;
	menu->button_level.height = menu->button_start.height;
	menu->button_level.pos.x = menu->button_start.pos.x;
	menu->button_level.pos.y = menu->button_start.pos.y + menu->button_start.height + cub3d->img->height * space_between_buttons;
	menu->button_level.background_color = BUTTON_COLOR;
	menu->button_level.border_color = BUTTON_BORDER_COLOR;
	menu->button_level.border_width = BUTTON_BORDER_THICKNESS;


	// set settings button
	menu->button_settings.width = menu->button_start.width;
	menu->button_settings.height = menu->button_start.height;
	menu->button_settings.pos.x = menu->button_start.pos.x;
	menu->button_settings.pos.y = menu->button_level.pos.y + menu->button_start.height + cub3d->img->height * space_between_buttons;
	menu->button_settings.background_color = BUTTON_COLOR;
	menu->button_settings.border_color = BUTTON_BORDER_COLOR;
	menu->button_settings.border_width = BUTTON_BORDER_THICKNESS;

	// set exit button
	menu->button_exit.width = menu->button_start.width;
	menu->button_exit.height = menu->button_start.height;
	menu->button_exit.pos.x = menu->button_start.pos.x;
	menu->button_exit.pos.y = menu->button_settings.pos.y + menu->button_start.height + cub3d->img->height * space_between_buttons;
	menu->button_exit.background_color = BUTTON_COLOR;
	menu->button_exit.border_color = BUTTON_BORDER_COLOR;
	menu->button_exit.border_width = BUTTON_BORDER_THICKNESS;

	// set background color
	menu->rect_title.color = GREEN;
	menu->background_color = BLACK;
}
