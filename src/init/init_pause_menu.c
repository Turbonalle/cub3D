#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void init_checkbox_info(pause_menu_t *menu, box_t *box, int pos_x, int pos_y)
{
	box->pos.x = pos_x;
	box->pos.y = pos_y;
	box->size = menu->rect_title.width * 0.08;
	box->border_width = fmax(box->size * 0.02, 2);
	box->border_color = BOX_BORDER_COLOR;
}

//------------------------------------------------------------------------------

void init_checkboxes(pause_menu_t *menu)
{
	init_checkbox_info(menu, &menu->box_fps[0], menu->pos_col_box_1, menu->pos_row_1);
	init_checkbox_info(menu, &menu->box_fps[1], menu->pos_col_box_2, menu->pos_row_1);
	init_checkbox_info(menu, &menu->box_fps[2], menu->pos_col_box_3, menu->pos_row_1);
	init_checkbox_info(menu, &menu->box_fps[3], menu->pos_col_box_4, menu->pos_row_1);
	init_checkbox_info(menu, &menu->box_fisheye[0], menu->pos_col_box_1, menu->pos_row_2);
	init_checkbox_info(menu, &menu->box_fisheye[1], menu->pos_col_box_2, menu->pos_row_2);
	init_checkbox_info(menu, &menu->box_mouse[0], menu->pos_col_box_1, menu->pos_row_3);
	init_checkbox_info(menu, &menu->box_mouse[1], menu->pos_col_box_2, menu->pos_row_3);
}

//------------------------------------------------------------------------------

void set_pause_menu_size(cub3d_t *cub3d, pause_menu_t *menu)
{
	float	menu_rect_width_percentage;
	float	menu_rect_height_percentage;

	menu_rect_width_percentage = 0.5;
	menu_rect_height_percentage = 0.9;
	menu->rect_title.width = cub3d->img->width * menu_rect_width_percentage;
	menu->rect_title.height = cub3d->img->height * menu_rect_height_percentage;
	menu->pos_x_rect_title = cub3d->img->width * ((1 - menu_rect_width_percentage) / 2);
	menu->pos_y_rect_title = cub3d->img->height * ((1 - menu_rect_height_percentage) / 2);
}

//------------------------------------------------------------------------------

void set_checkbox_positions(pause_menu_t *menu)
{
	menu->pos_col_text = menu->pos_x_rect_title + menu->rect_title.width * 0.05;
	menu->pos_col_box_1 = menu->pos_x_rect_title + menu->rect_title.width * 0.2;
	menu->pos_col_box_2 = menu->pos_x_rect_title + menu->rect_title.width * 0.35;
	menu->pos_col_box_3 = menu->pos_x_rect_title + menu->rect_title.width * 0.5;
	menu->pos_col_box_4 = menu->pos_x_rect_title + menu->rect_title.width * 0.65;
	menu->pos_col_box_5 = menu->pos_x_rect_title + menu->rect_title.width * 0.8;
	menu->pos_row_1 = menu->rect_title.height * 0.4;
	menu->pos_row_2 = menu->rect_title.height * 0.6;
	menu->pos_row_3 = menu->rect_title.height * 0.8;
}

void set_pause_title(pause_menu_t *menu)
{
	menu->rect_title.pos.x = menu->pos_x_rect_title;
	menu->rect_title.pos.y = menu->pos_y_rect_title;
	// menu->rect_title.color = PAUSE_MENU_SETTINGS_RECT_COLOR;
	// menu->rect_title.color = 0x1B1129FF;	// dark purple
	// menu->rect_title.color = 0x151F33FF;	// dark blue
	menu->rect_title.color = 0x0E1421FF;	// darker blue

}

//------------------------------------------------------------------------------

void set_checkbox_values(pause_menu_t *menu)
{
	menu->box_fps[0].value = 15;
	menu->box_fps[1].value = 30;
	menu->box_fps[2].value = 60;
	menu->box_fps[3].value = 120;
	menu->box_fisheye[0].value = ON;
	menu->box_fisheye[1].value = OFF;
	menu->box_mouse[0].value = ON;
	menu->box_mouse[1].value = OFF;
}

//------------------------------------------------------------------------------

void	init_checkbox_states(pause_menu_t *menu)
{
	menu->box_fps[0].state = FALSE;
	menu->box_fps[1].state = FALSE;
	menu->box_fps[2].state = TRUE;
	menu->box_fps[3].state = FALSE;
	menu->box_fisheye[0].state = FALSE;
	menu->box_fisheye[1].state = TRUE;
	menu->box_mouse[0].state = FALSE;
	menu->box_mouse[1].state = TRUE;
}

//------------------------------------------------------------------------------

void init_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	cub3d->pause_menu.background_color = set_transparency(PAUSE_MENU_BACKGROUND_COLOR, PAUSE_MENU_TRANSPARENCY);
	set_pause_menu_size(cub3d, menu);
	set_checkbox_positions(menu);
	set_pause_title(menu);
	init_checkboxes(menu);
	set_checkbox_values(menu);
	init_checkbox_states(menu);
}

