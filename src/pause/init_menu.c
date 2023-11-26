#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void set_menu_background(cub3d_t *cub3d, pause_menu_t *menu)
{
	unsigned int	row;
	unsigned int	column;

	row = -1;
	while (++row < cub3d->img->height)
	{
		column = -1;
		while (++column < cub3d->img->width)
			mlx_put_pixel(cub3d->pause_menu.img, column, row, menu->background_color);
	}
}

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

void init_pause_menu_values(cub3d_t *cub3d, pause_menu_t *menu)
{
	float	menu_rect_width_percentage;
	float	menu_rect_height_percentage;

	menu_rect_width_percentage = 0.5;
	menu_rect_height_percentage = 0.9;
	menu->rect_title.width = cub3d->img->width * menu_rect_width_percentage;
	menu->rect_title.height = cub3d->img->height * menu_rect_height_percentage;
	menu->pos_x_rect_title = cub3d->img->width * ((1 - menu_rect_width_percentage) / 2);
	menu->pos_y_rect_title = cub3d->img->height * ((1 - menu_rect_height_percentage) / 2);
	menu->pos_col_text = menu->pos_x_rect_title + menu->rect_title.width * 0.05;
	menu->pos_col_box_1 = menu->pos_x_rect_title + menu->rect_title.width * 0.2;
	menu->pos_col_box_2 = menu->pos_x_rect_title + menu->rect_title.width * 0.35;
	menu->pos_col_box_3 = menu->pos_x_rect_title + menu->rect_title.width * 0.5;
	menu->pos_col_box_4 = menu->pos_x_rect_title + menu->rect_title.width * 0.65;
	menu->pos_col_box_5 = menu->pos_x_rect_title + menu->rect_title.width * 0.8;
	menu->pos_row_1 = menu->rect_title.height * 0.4;
	menu->pos_row_2 = menu->rect_title.height * 0.6;
	menu->pos_row_3 = menu->rect_title.height * 0.8;
	menu->rect_title.pos.x = menu->pos_x_rect_title;
	menu->rect_title.pos.y = menu->pos_y_rect_title;
	menu->rect_title.color = PAUSE_MENU_SETTINGS_RECT_COLOR;
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

void set_checkbox_values(cub3d_t *cub3d, pause_menu_t *menu)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (cub3d->settings.fps == i)
			menu->box_fps[i].value = TRUE;
		else
			menu->box_fps[i].value = FALSE;
	}
	i = -1;
	while (++i < 2)
	{
		if (cub3d->settings.fisheye == i)
			menu->box_fisheye[i].value = TRUE;
		else
			menu->box_fisheye[i].value = FALSE;
	}
	i = -1;
	while (++i < 2)
	{
		if (cub3d->settings.mouse == i)
			menu->box_mouse[i].value = TRUE;
		else
			menu->box_mouse[i].value = FALSE;
	}
}

//------------------------------------------------------------------------------

void draw_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	draw_rectangle(cub3d, &menu->rect_title);
	draw_checkbox(cub3d, &menu->box_fps[0]);
	draw_checkbox(cub3d, &menu->box_fps[1]);
	draw_checkbox(cub3d, &menu->box_fps[2]);
	draw_checkbox(cub3d, &menu->box_fps[3]);
	draw_checkbox(cub3d, &menu->box_fisheye[0]);
	draw_checkbox(cub3d, &menu->box_fisheye[1]);
	draw_checkbox(cub3d, &menu->box_mouse[0]);
	draw_checkbox(cub3d, &menu->box_mouse[1]);
}

//------------------------------------------------------------------------------

void init_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create pause menu image");
	
	cub3d->pause_menu.background_color = set_transparency(PAUSE_MENU_BACKGROUND_COLOR, PAUSE_MENU_TRANSPARENCY);
	set_menu_background(cub3d, menu);
	init_pause_menu_values(cub3d, menu);
	set_checkbox_values(cub3d, menu);
	draw_pause_menu(cub3d, menu);

	mlx_image_to_window(cub3d->mlx, cub3d->pause_menu.img, 0, 0);
	
	add_title_text(cub3d, menu);
	add_category_text(cub3d, menu);
	add_checkbox_text(cub3d, menu);
}