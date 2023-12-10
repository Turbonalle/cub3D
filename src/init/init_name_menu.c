#include "../incl/cub3d.h"

void	init_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	menu->background_color = BLACK;
	menu->changed = FALSE;
	menu->current = 0;

	// set title
	menu->rect_title.width = cub3d->mlx->width * 0.4;
	menu->rect_title.height = cub3d->mlx->height * 0.15;
	menu->rect_title.pos.x = (cub3d->mlx->width - menu->rect_title.width) / 2;
	menu->rect_title.pos.y = cub3d->mlx->height * 0.05;
	menu->rect_title.color = GREEN;

	// set title text
	

	// set name input
	menu->rect_input.width = cub3d->mlx->width * 0.4;
	menu->rect_input.height = cub3d->mlx->height * 0.15;
	menu->rect_input.pos.x = (cub3d->mlx->width - menu->rect_input.width) / 2;
	menu->rect_input.pos.y = cub3d->mlx->height * 0.3;
	menu->rect_input.color = GREEN;

	// set letter fields
	int i = -1;
	while (++i < MAX_NAME_LENGTH)
	{
		menu->box[i].width = menu->rect_input.width / MAX_NAME_LENGTH;
		menu->box[i].height = menu->rect_input.height;
		menu->box[i].pos.x = menu->rect_input.pos.x + i * menu->box[i].width;
		menu->box[i].pos.y = menu->rect_input.pos.y;
		menu->box[i].background_color = BOX_OFF_COLOR;
		menu->box[i].border_color = BOX_BORDER_COLOR;
		menu->box[i].border_width = 1;
		menu->box[i].letter[0] = '\0';
		menu->box[i].letter[1] = '\0';
	}
}