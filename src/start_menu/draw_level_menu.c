#include "../incl/cub3d.h"

void	draw_level_menu(cub3d_t *cub3d, level_menu_t *menu)
{
	int i;

	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create pause menu image");

	draw_menu_background(menu->img, menu->background_color);

	i = -1;
	while (++i < 9)
		draw_button(menu->img, &menu->buttons[i]);

	mlx_image_to_window(cub3d->mlx, menu->img, 0, 0);
	menu->text_level_1 = mlx_put_string(cub3d->mlx, "Level 1", menu->buttons[i].pos.x + menu->buttons[i].width * 0.5, menu->buttons[i].pos.y + menu->buttons[i].height * 0.5);
	center(menu->text_level_1);
	menu->text_level_2 = mlx_put_string(cub3d->mlx, "Level 2", menu->buttons[i].pos.x + menu->buttons[i].width * 0.5, menu->buttons[i].pos.y + menu->buttons[i].height * 0.5);
	center(menu->text_level_2);
	menu->text_level_3 = mlx_put_string(cub3d->mlx, "Level 3", menu->buttons[i].pos.x + menu->buttons[i].width * 0.5, menu->buttons[i].pos.y + menu->buttons[i].height * 0.5);
	center(menu->text_level_3);
	menu->text_level_4 = mlx_put_string(cub3d->mlx, "Level 4", menu->buttons[i].pos.x + menu->buttons[i].width * 0.5, menu->buttons[i].pos.y + menu->buttons[i].height * 0.5);
	center(menu->text_level_4);
	menu->text_level_5 = mlx_put_string(cub3d->mlx, "Level 5", menu->buttons[i].pos.x + menu->buttons[i].width * 0.5, menu->buttons[i].pos.y + menu->buttons[i].height * 0.5);
	center(menu->text_level_5);
	menu->text_level_6 = mlx_put_string(cub3d->mlx, "Level 6", menu->buttons[i].pos.x + menu->buttons[i].width * 0.5, menu->buttons[i].pos.y + menu->buttons[i].height * 0.5);
	center(menu->text_level_6);
	menu->text_level_7 = mlx_put_string(cub3d->mlx, "Level 7", menu->buttons[i].pos.x + menu->buttons[i].width * 0.5, menu->buttons[i].pos.y + menu->buttons[i].height * 0.5);
	center(menu->text_level_7);
	menu->text_level_8 = mlx_put_string(cub3d->mlx, "Level 8", menu->buttons[i].pos.x + menu->buttons[i].width * 0.5, menu->buttons[i].pos.y + menu->buttons[i].height * 0.5);
	center(menu->text_level_8);
	menu->text_level_9 = mlx_put_string(cub3d->mlx, "Level 9", menu->buttons[i].pos.x + menu->buttons[i].width * 0.5, menu->buttons[i].pos.y + menu->buttons[i].height * 0.5);
	center(menu->text_level_9);
}