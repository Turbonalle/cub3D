#include "cub3d.h"

void add_category_text(cub3d_t *cub3d, pause_menu_t *menu)
{
	menu->text_fps = mlx_put_string(cub3d->mlx, "FPS:", menu->pos_col_text, menu->pos_row_1);
	menu->text_fps->instances[0].y = menu->pos_row_1 + menu->box_fps[0].size * 0.5 - menu->text_fps->height * 0.5;
	menu->text_fisheye = mlx_put_string(cub3d->mlx, "Fisheye:", menu->pos_col_text, menu->pos_row_2);
	menu->text_fisheye->instances[0].y = menu->pos_row_2 + menu->box_fps[0].size * 0.5 - menu->text_fisheye->height * 0.5;
	menu->text_mouse = mlx_put_string(cub3d->mlx, "Mouse:", menu->pos_col_text, menu->pos_row_3);
	menu->text_mouse->instances[0].y = menu->pos_row_3 + menu->box_fps[0].size * 0.5 - menu->text_mouse->height * 0.5;
	menu->text_mouse_sensitivity = mlx_put_string(cub3d->mlx, "Sensitivity:", menu->pos_col_text, menu->pos_row_4);
	menu->text_mouse_sensitivity->instances[0].y = menu->pos_row_4 + menu->box_fps[0].size * 0.5 - menu->text_mouse_sensitivity->height * 0.5;
}

void add_checkbox_text(cub3d_t *cub3d, pause_menu_t *menu)
{
	menu->box_fps[0].text = mlx_put_string(cub3d->mlx, "15", menu->pos_col_box_1 + menu->box_fps[0].size * 0.5, menu->pos_row_1 + menu->box_fps[0].size * 0.5);
	center(menu->box_fps[0].text);
	menu->box_fps[1].text = mlx_put_string(cub3d->mlx, "30", menu->pos_col_box_2 + menu->box_fps[1].size * 0.5, menu->pos_row_1 + menu->box_fps[1].size * 0.5);
	center(menu->box_fps[1].text);
	menu->box_fps[2].text = mlx_put_string(cub3d->mlx, "60", menu->pos_col_box_3 + menu->box_fps[2].size * 0.5, menu->pos_row_1 + menu->box_fps[2].size * 0.5);
	center(menu->box_fps[2].text);
	menu->box_fps[3].text = mlx_put_string(cub3d->mlx, "120", menu->pos_col_box_4 + menu->box_fps[3].size * 0.5, menu->pos_row_1 + menu->box_fps[3].size * 0.5);
	center(menu->box_fps[3].text);
	menu->box_fisheye[0].text = mlx_put_string(cub3d->mlx, "On", menu->pos_col_box_1 + menu->box_fisheye[0].size * 0.5, menu->pos_row_2 + menu->box_fisheye[0].size * 0.5);
	center(menu->box_fisheye[0].text);
	menu->box_fisheye[1].text = mlx_put_string(cub3d->mlx, "Off", menu->pos_col_box_2 + menu->box_fisheye[1].size * 0.5, menu->pos_row_2 + menu->box_fisheye[1].size * 0.5);
	center(menu->box_fisheye[1].text);
	menu->box_mouse[0].text = mlx_put_string(cub3d->mlx, "On", menu->pos_col_box_1 + menu->box_mouse[0].size * 0.5, menu->pos_row_3 + menu->box_mouse[0].size * 0.5);
	center(menu->box_mouse[0].text);
	menu->box_mouse[1].text = mlx_put_string(cub3d->mlx, "Off", menu->pos_col_box_2 + menu->box_mouse[1].size * 0.5, menu->pos_row_3 + menu->box_mouse[1].size * 0.5);
	center(menu->box_mouse[1].text);
}