#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void init_checkbox_info(pause_menu_t *menu, box_t *box, int pos_x, int pos_y)
{
	box->pos.x = pos_x - menu->menu_pos.x;
	box->pos.y = pos_y - menu->menu_pos.y;
	// box->pos.x = pos_x;
	// box->pos.y = pos_y;
	box->size = menu->menu->width * 0.08;
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

static void load_png(pause_menu_t *menu)
{
	menu->title.texture = mlx_load_png(PAUSE_PNG);
}

static int init_images(mlx_t *mlx, pause_menu_t *menu)
{
	menu->bg = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!menu->bg)
		return (err("Failed to create image"));
	menu->menu = mlx_new_image(mlx, mlx->width * 0.5, mlx->height * 0.9);
	if (!menu->menu)
		return (err("Failed to create image"));
	menu->title.img = mlx_texture_to_image(mlx, menu->title.texture);
	if (!menu->title.img)
		return (err("Failed to create image"));
	return (SUCCESS);
}

static void set_positions(pause_menu_t *menu)
{
	// set menu pos (inner rectangle)
	menu->menu_pos.x = (menu->bg->width - menu->menu->width) / 2;
	menu->menu_pos.y = (menu->bg->height - menu->menu->height) / 2;
	
	// set title pos
	menu->title.pos.x = menu->menu_pos.x + (menu->menu->width - menu->title.img->width) / 2;
	menu->title.pos.y = menu->menu_pos.y + menu->menu->height * 0.15;

	// set checkbox pos
	menu->pos_col_text = menu->menu_pos.x + menu->menu->width * 0.1;
	menu->pos_col_box_1 = menu->menu_pos.x + menu->menu->width * 0.25;
	menu->pos_col_box_2 = menu->menu_pos.x + menu->menu->width * 0.35;
	menu->pos_col_box_3 = menu->menu_pos.x + menu->menu->width * 0.45;
	menu->pos_col_box_4 = menu->menu_pos.x + menu->menu->width * 0.55;
	menu->pos_col_box_5 = menu->menu_pos.x + menu->menu->width * 0.65;
	menu->pos_row_1 = menu->menu->height * 0.4;
	menu->pos_row_2 = menu->menu->height * 0.55;
	menu->pos_row_3 = menu->menu->height * 0.7;
}

static int put_images_to_window(mlx_t *mlx, pause_menu_t *menu)
{
	if (mlx_image_to_window(mlx, menu->bg, 0, 0) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->menu, menu->menu_pos.x, menu->menu_pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->title.img, menu->title.pos.x, menu->title.pos.y) < 0)
		return (err("Failed to put image to window"));
	return (SUCCESS);
}

int init_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	printf("init_pause_menu\n");
	load_png(menu);
	if (!init_images(cub3d->mlx, menu))
		return (FAIL);
	set_positions(menu);
	init_checkboxes(menu);
	set_checkbox_values(menu);
	init_checkbox_states(menu);
	cub3d->settings.e_speed = 1;
	update_settings(cub3d, menu);

	draw_menu_background(menu->bg, set_transparency(PAUSE_MENU_BACKGROUND_COLOR, PAUSE_MENU_TRANSPARENCY));
	draw_menu_background(menu->menu, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->menu);

	if (!put_images_to_window(cub3d->mlx, menu))
		return (FAIL);
	add_category_text(cub3d, menu);
	add_checkbox_text(cub3d, menu);

	printf("disabling pause menu\n");
	disable_pause_menu(cub3d->mlx, menu);
	printf("init_pause_menu end\n");
	return (SUCCESS);
}

