#include "../incl/cub3d.h"

void	draw_letter_box(mlx_image_t *img, letter_box_t *box)
{
	int col;
	int row;

	row = box->pos.y - 1;
	while (++row < box->height + box->pos.y)
	{
		col = box->pos.x - 1;
		while (++col < box->width + box->pos.x)
		{
			if (row < box->pos.y + box->border_width || row >= box->pos.y + box->width - box->border_width)
				mlx_put_pixel(img, col, row, box->border_color);
			else if (col < box->pos.x + box->border_width || col >= box->pos.x + box->width - box->border_width)
				mlx_put_pixel(img, col, row, box->border_color);
			else
				mlx_put_pixel(img, col, row, box->background_color);
		}
	}
}

void	init_letter_images(cub3d_t *cub3d, name_menu_t *menu)
{
	int i;

	i = -1;
	while (++i < ALPHABET_LENGTH)
	{
		menu->letter_str[i][0] = ALPHABET[i];
		menu->letter_str[i][1] = '\0';
		menu->letters_img[i] = mlx_put_string(cub3d->mlx, menu->letter_str[i], 0, 0);
		menu->letters_img[i]->instances[0].enabled = FALSE;
	}
}

static void load_png(name_menu_t *menu)
{
	menu->timer.texture = mlx_load_png(TIMER_PNG);
	menu->back.texture = mlx_load_png(BACK_PNG);
	menu->back_hover.texture = mlx_load_png(BACK_HOVER_PNG);
}

static int init_images(mlx_t *mlx, name_menu_t *menu)
{
	menu->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!menu->img)
		return (err("Failed to create name menu image"));
	menu->back.img = mlx_texture_to_image(mlx, menu->back.texture);
	if (!menu->back.img)
		return (err("Failed to create name menu back image"));
	menu->back_hover.img = mlx_texture_to_image(mlx, menu->back_hover.texture);
	if (!menu->back_hover.img)
		return (err("Failed to create name menu back hover image"));
	menu->timer.img = mlx_texture_to_image(mlx, menu->timer.texture);
	if (!menu->timer.img)
		return (err("Failed to create timer image"));
	return (SUCCESS);
}

static void set_letter_fields(name_menu_t *menu)
{
	int	i;

	i = -1;
	while (++i < MAX_NAME_LENGTH)
	{
		menu->box[i].width = (menu->rect_input.width - (NAME_BOX_GAP * (MAX_NAME_LENGTH - 1))) / MAX_NAME_LENGTH;
		menu->box[i].height = menu->rect_input.height;
		menu->box[i].pos.x = menu->rect_input.pos.x + i * menu->box[i].width + i * NAME_BOX_GAP;
		menu->box[i].pos.y = menu->rect_input.pos.y;
		menu->box[i].background_color = BOX_OFF_COLOR;
		menu->box[i].border_color = BOX_BORDER_COLOR;
		menu->box[i].border_width = 1;
		menu->box[i].letter[0] = '\0';
		menu->box[i].letter[1] = '\0';
	}
}

static void set_positions(name_menu_t *menu, vector_t back_button_pos)
{
	// set title
	menu->rect_title.width = menu->img->width * 0.4;
	menu->rect_title.height = menu->img->height * 0.15;
	menu->rect_title.pos.x = (menu->img->width - menu->rect_title.width) / 2;
	menu->rect_title.pos.y = menu->img->height * 0.12;
	menu->rect_title.color = GREEN;

	// set back button
	menu->back.pos.x = back_button_pos.x;
	menu->back.pos.y = back_button_pos.y;
	menu->back_hover.pos.x = back_button_pos.x;
	menu->back_hover.pos.y = back_button_pos.y;

	// set timer
	menu->timer.pos.x = menu->img->width * 0.5 - menu->timer.img->width * 0.5;
	menu->timer.pos.y = menu->img->height * 0.4 - menu->timer.img->height * 0.5;

	// set name input
	menu->rect_input.width = menu->img->width * 0.6;
	menu->rect_input.height = (menu->rect_input.width - (NAME_BOX_GAP * (MAX_NAME_LENGTH - 1))) / MAX_NAME_LENGTH;
	menu->rect_input.pos.x = (menu->img->width - menu->rect_input.width) / 2;
	menu->rect_input.pos.y = menu->img->height * 0.6;
	menu->rect_input.color = WHITE;

	set_letter_fields(menu);
}

static int put_images_to_window(mlx_t *mlx, name_menu_t *menu)
{
	if (mlx_image_to_window(mlx, menu->img, 0, 0) < 0)
		return (err("Failed to put name menu image to window"));
	if (mlx_image_to_window(mlx, menu->back.img, menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put name menu back image to window"));
	if (mlx_image_to_window(mlx, menu->back_hover.img, menu->back_hover.pos.x, menu->back_hover.pos.y) < 0)
		return (err("Failed to put name menu back hover image to window"));
	if (mlx_image_to_window(mlx, menu->timer.img, menu->timer.pos.x, menu->timer.pos.y) < 0)
		return (err("Failed to put timer image to window"));
	menu->text_win_message = mlx_put_string(mlx, "You got a top 3 score!", menu->rect_title.pos.x + menu->rect_title.width * 0.5, menu->rect_title.pos.y + menu->rect_title.height * 0.5);
	center(menu->text_win_message);
	return (SUCCESS);
}

static void init_values(name_menu_t *menu)
{
	int	i;

	i = -1;
	while (++i < MAX_NAME_LENGTH)
	{
		menu->name[i] = '\0';
		menu->letter_index[i] = 0;
	}
	menu->changed = FALSE;
	menu->current = 0;
}

int	init_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	int	i;

	load_png(menu);
	if (!init_images(cub3d->mlx, menu))
		return (err("Failed to init name menu images"));
	set_positions(menu, cub3d->back_button_pos);
	init_values(menu);
	draw_background(menu->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->img);
	draw_rectangle(menu->img, &menu->rect_title);
	i = -1;
	while (++i < MAX_NAME_LENGTH)
		draw_letter_box(menu->img, &menu->box[i]);
	if (!put_images_to_window(cub3d->mlx, menu))
		return (FAIL);
	init_letter_images(cub3d, menu);
	disable_name_menu(cub3d->mlx, menu);
	return (SUCCESS);
}