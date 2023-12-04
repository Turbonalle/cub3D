#include "../incl/cub3d.h"

void	init_level_buttons(cub3d_t *cub3d, level_menu_t *menu)
{
	int	i;

	i = -1;
	while (++i < 9)
	{
		menu->buttons[i].width = cub3d->mlx->width * 0.2;
		menu->buttons[i].height = cub3d->mlx->height * 0.15;
		menu->buttons[i].pos.x = cub3d->mlx->width * 0.1 + (i % 3) * (menu->buttons[i].width + cub3d->mlx->width * 0.1);
		menu->buttons[i].pos.y = cub3d->mlx->height * 0.3 + (i / 3) * (menu->buttons[i].height + cub3d->mlx->height * 0.1);
		menu->buttons[i].background_color = BUTTON_COLOR;
		menu->buttons[i].border_color = BUTTON_BORDER_COLOR;
		menu->buttons[i].border_width = BUTTON_BORDER_THICKNESS;
	}
	// set back button
	menu->button_back.width = cub3d->mlx->height * 0.15;
	menu->button_back.height = cub3d->mlx->height * 0.15;
	menu->button_back.pos.x = cub3d->mlx->width * 0.1;
	menu->button_back.pos.y = cub3d->mlx->height * 0.05;
	menu->button_back.background_color = BUTTON_COLOR;
	menu->button_back.border_color = BUTTON_BORDER_COLOR;
	menu->button_back.border_width = BUTTON_BORDER_THICKNESS;
}

void	init_level_menu(cub3d_t *cub3d, level_menu_t *menu)
{
	menu->background_color = BLACK;
	menu->rect_title.width = cub3d->mlx->width * 0.4;
	menu->rect_title.height = cub3d->mlx->height * 0.15;
	menu->rect_title.pos.x = (cub3d->mlx->width - menu->rect_title.width) / 2;
	menu->rect_title.pos.y = cub3d->mlx->height * 0.05;
	menu->rect_title.color = GREEN;
	init_level_buttons(cub3d, menu);
}
