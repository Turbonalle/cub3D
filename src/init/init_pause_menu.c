#include "../incl/cub3d.h"

//------------------------------------------------------------------------------

void init_checkbox_info(pause_menu_t *menu, box_t *box, int pos_x, int pos_y)
{
	box->pos.x = pos_x - menu->menu_pos.x;
	box->pos.y = pos_y - menu->menu_pos.y;
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

int	init_sensitivity_slider(cub3d_t *cub3d, pause_menu_t *menu)
{
	// set slider
	// menu->sensitivity_slider.pos.x = menu->pos_col_box_1 - menu->menu_pos.x;
	// menu->sensitivity_slider.pos.y = menu->pos_row_4 - menu->menu_pos.y + menu->box_fps[0].size * 0.5 - SLIDER_LINE_WIDTH * 0.5;
	menu->sensitivity_slider.pos.x = menu->pos_col_box_1;
	menu->sensitivity_slider.pos.y = menu->pos_row_4 + menu->box_fps[0].size * 0.5 - SLIDER_LINE_WIDTH * 0.5;

	menu->sensitivity_slider.length = menu->pos_col_box_4 - menu->pos_col_box_1 + menu->box_fps[0].size;
	menu->sensitivity_slider.value = MOUSE_SENSITIVITY;

	// set slider marker
	menu->sensitivity_slider.on_marker = FALSE;
	menu->sensitivity_slider.marker_min_pos = menu->sensitivity_slider.pos.x + SLIDER_LINE_WIDTH;
	menu->sensitivity_slider.marker_max_pos = menu->sensitivity_slider.pos.x + menu->sensitivity_slider.length - SLIDER_LINE_WIDTH;

	// set slider marker img
	menu->sensitivity_slider.marker = mlx_new_image(cub3d->mlx, SLIDER_MARKER_WIDTH, SLIDER_MARKER_HEIGHT);
	if (!menu->sensitivity_slider.marker)
		return (err("Failed to create image"));
	menu->sensitivity_slider.marker_pos.x = get_marker_pos(cub3d);
	menu->sensitivity_slider.marker_pos.y = menu->sensitivity_slider.pos.y + SLIDER_LINE_WIDTH / 2 - SLIDER_MARKER_HEIGHT / 2;
	menu->sensitivity_slider.marker_pos.x += menu->sensitivity_slider.pos.x - menu->menu_pos.x;
	if (mlx_image_to_window(cub3d->mlx, menu->sensitivity_slider.marker, menu->sensitivity_slider.marker_pos.x, menu->sensitivity_slider.marker_pos.y) < 0)
		return (err("Failed to put image to window"));
	return (SUCCESS);
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
	int	gap_x;
	int	gap_y;

	// set gaps
	gap_x = menu->menu->width * 0.10;
	gap_y = menu->menu->height * 0.13;

	// set menu pos (inner rectangle)
	menu->menu_pos.x = (menu->bg->width - menu->menu->width) / 2;
	menu->menu_pos.y = (menu->bg->height - menu->menu->height) / 2;
	
	// set title pos
	menu->title.pos.x = menu->menu_pos.x + (menu->menu->width - menu->title.img->width) / 2;
	menu->title.pos.y = menu->menu_pos.y + menu->menu->height * 0.15;

	// set checkbox pos
	menu->pos_col_text = menu->menu_pos.x + menu->menu->width * 0.15;
	menu->pos_col_box_1 = menu->menu_pos.x + menu->menu->width * 0.38;
	menu->pos_col_box_2 = menu->pos_col_box_1 + gap_x;
	menu->pos_col_box_3 = menu->pos_col_box_2 + gap_x;
	menu->pos_col_box_4 = menu->pos_col_box_3 + gap_x;
	menu->pos_col_box_5 = menu->pos_col_box_4 + gap_x;
	menu->pos_row_1 = menu->menu_pos.y + menu->menu->height * 0.4;
	menu->pos_row_2 = menu->pos_row_1 + gap_y;
	menu->pos_row_3 = menu->pos_row_2 + gap_y;
	menu->pos_row_4 = menu->pos_row_3 + gap_y;
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
	load_png(menu);
	if (!init_images(cub3d->mlx, menu))
		return (FAIL);
	set_positions(menu);
	init_checkboxes(menu);
	set_checkbox_values(menu);
	init_checkbox_states(menu);

	if (!put_images_to_window(cub3d->mlx, menu))
		return (FAIL);

	init_sensitivity_slider(cub3d, menu);
	update_settings(cub3d, menu);

	draw_background(menu->bg, set_transparency(PAUSE_MENU_BACKGROUND_COLOR, PAUSE_MENU_TRANSPARENCY));
	draw_background(menu->menu, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->menu);
	draw_slider(menu->menu, &menu->sensitivity_slider);

	add_category_text(cub3d, menu);
	add_checkbox_text(cub3d, menu);

	disable_pause_menu(cub3d->mlx, menu);
	return (SUCCESS);
}

