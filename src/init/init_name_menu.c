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

void	init_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	int	gap;

	menu->background_color = BLACK;
	menu->changed = FALSE;
	menu->current = 0;

	int i = -1;
	while (++i < MAX_NAME_LENGTH)
		menu->name[i] = '\0';

	// set title
	menu->rect_title.width = cub3d->mlx->width * 0.4;
	menu->rect_title.height = cub3d->mlx->height * 0.15;
	menu->rect_title.pos.x = (cub3d->mlx->width - menu->rect_title.width) / 2;
	menu->rect_title.pos.y = cub3d->mlx->height * 0.05;
	menu->rect_title.color = GREEN;

	gap = 5;

	// set name input
	menu->rect_input.width = cub3d->mlx->width * 0.8;
	menu->rect_input.height = (menu->rect_input.width - (gap * (MAX_NAME_LENGTH - 1))) / MAX_NAME_LENGTH;
	menu->rect_input.pos.x = (cub3d->mlx->width - menu->rect_input.width) / 2;
	menu->rect_input.pos.y = cub3d->mlx->height * 0.5;
	menu->rect_input.color = WHITE;

	// set letter fields
	i = -1;
	while (++i < MAX_NAME_LENGTH)
	{
		menu->box[i].width = (menu->rect_input.width - (gap * (MAX_NAME_LENGTH - 1))) / MAX_NAME_LENGTH;
		menu->box[i].height = menu->rect_input.height;
		menu->box[i].pos.x = menu->rect_input.pos.x + i * menu->box[i].width + i * gap;
		menu->box[i].pos.y = menu->rect_input.pos.y;
		menu->box[i].background_color = BOX_OFF_COLOR;
		menu->box[i].border_color = BOX_BORDER_COLOR;
		menu->box[i].border_width = 1;
		menu->box[i].letter[0] = '\0';
		menu->box[i].letter[1] = '\0';
	}

	// create image
	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create name menu image");

	// draw background
	draw_menu_background(menu->img, menu->background_color);

	// draw win message
	draw_rectangle(menu->img, &menu->rect_title);

	// draw name input
	i = -1;
	while (++i < MAX_NAME_LENGTH)
		draw_letter_box(menu->img, &menu->box[i]);

	mlx_image_to_window(cub3d->mlx, menu->img, 0, 0);


	menu->img->instances[0].enabled = FALSE;
	menu->text_win_message = mlx_put_string(cub3d->mlx, "You got a top 5 score!", menu->rect_title.pos.x + menu->rect_title.width * 0.5, menu->rect_title.pos.y + menu->rect_title.height * 0.5);
	menu->text_win_message->instances[0].enabled = FALSE;
}