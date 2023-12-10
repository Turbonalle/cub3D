#include "../incl/cub3d.h"

void	draw_letter_box(mlx_image_t *img, letter_box_t *box)
{
	int col;
	int row;

	row = -1;
	while (++row < box->height)
	{
		col = -1;
		while (++col < box->width)
		{
			if (row < box->pos.y + box->border_width || row > box->pos.y + box->size - box->border_width)
				mlx_put_pixel(img, col, row, box->border_color);
			else if (col < box->pos.x + box->border_width || col > box->pos.x + box->size - box->border_width)
				mlx_put_pixel(img, col, row, box->border_color);
			else
				mlx_put_pixel(img, col, row, box->background_color);
		}
	}
}

int	draw_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	// int	i;

	printf("Creating image\n");
	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create name menu image");

	// draw background
	printf("Drawing background\n");
	draw_menu_background(menu->img, menu->background_color);

	// // draw win message
	// printf("Drawing win message\n");
	// draw_rectangle(menu->img, &menu->rect_title);

	// printf("Putting string\n");
	// menu->text_win_message = mlx_put_string(cub3d->mlx, "You got a top 5 score!", menu->rect_title.pos.x + menu->rect_title.width * 0.5, menu->rect_title.pos.y + menu->rect_title.height * 0.5);
	// printf("Centering string\n");
	// center(menu->text_win_message);

	// // draw name input
	// // draw_rect(cub3d->img, &menu->rect_input);
	// printf("Drawing name input\n");
	// i = -1;
	// while (++i < MAX_NAME_LENGTH)
	// 	draw_letter_box(menu->img, &menu->box[i]);

	printf("Adding name menu to window\n");
	mlx_image_to_window(cub3d->mlx, menu->img, menu->rect_title.pos.x, menu->rect_title.pos.y);

	return (SUCCESS);
}