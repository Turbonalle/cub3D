#include "../incl/cub3d.h"

void	init_level_buttons(cub3d_t *cub3d, level_menu_t *menu)
{
	int	i;

	i = -1;
	while (++i < cub3d->n_levels)
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
	// set leaderboard button
	menu->button_leaderboard.width = cub3d->mlx->width * 0.1;
	menu->button_leaderboard.height = cub3d->mlx->height * 0.15;
	menu->button_leaderboard.pos.x = cub3d->mlx->width * 0.8;
	menu->button_leaderboard.pos.y = cub3d->mlx->height * 0.05;
	menu->button_leaderboard.background_color = BUTTON_COLOR;
	menu->button_leaderboard.border_color = BUTTON_BORDER_COLOR;
	menu->button_leaderboard.border_width = BUTTON_BORDER_THICKNESS;
}

void	init_level_menu(cub3d_t *cub3d, level_menu_t *menu)
{
	int i;

	menu->background_color = BLACK;
	menu->rect_title.width = cub3d->mlx->width * 0.4;
	menu->rect_title.height = cub3d->mlx->height * 0.15;
	menu->rect_title.pos.x = (cub3d->mlx->width - menu->rect_title.width) / 2;
	menu->rect_title.pos.y = cub3d->mlx->height * 0.05;
	menu->rect_title.color = GREEN;
	init_level_buttons(cub3d, menu);


	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create pause menu image");

	draw_menu_background(menu->img, menu->background_color);

	draw_rectangle(menu->img, &menu->rect_title);

	i = -1;
	while (++i < cub3d->n_levels)
		draw_button(menu->img, &menu->buttons[i]);

	mlx_image_to_window(cub3d->mlx, menu->img, 0, 0);
	menu->text_title = mlx_put_string(cub3d->mlx, "Select Level", menu->rect_title.pos.x + menu->rect_title.width * 0.5, menu->rect_title.pos.y + menu->rect_title.height * 0.5);
	center(menu->text_title);
	menu->text_level_1 = mlx_put_string(cub3d->mlx, "Level 1", menu->buttons[0].pos.x + menu->buttons[0].width * 0.5, menu->buttons[0].pos.y + menu->buttons[0].height * 0.5);
	center(menu->text_level_1);
	menu->text_level_2 = mlx_put_string(cub3d->mlx, "Level 2", menu->buttons[1].pos.x + menu->buttons[1].width * 0.5, menu->buttons[1].pos.y + menu->buttons[1].height * 0.5);
	center(menu->text_level_2);
	menu->text_level_3 = mlx_put_string(cub3d->mlx, "Level 3", menu->buttons[2].pos.x + menu->buttons[2].width * 0.5, menu->buttons[2].pos.y + menu->buttons[2].height * 0.5);
	center(menu->text_level_3);
	menu->text_level_4 = mlx_put_string(cub3d->mlx, "Level 4", menu->buttons[3].pos.x + menu->buttons[3].width * 0.5, menu->buttons[3].pos.y + menu->buttons[3].height * 0.5);
	center(menu->text_level_4);
	menu->text_level_5 = mlx_put_string(cub3d->mlx, "Level 5", menu->buttons[4].pos.x + menu->buttons[4].width * 0.5, menu->buttons[4].pos.y + menu->buttons[4].height * 0.5);
	center(menu->text_level_5);
	menu->text_level_6 = mlx_put_string(cub3d->mlx, "Level 6", menu->buttons[5].pos.x + menu->buttons[5].width * 0.5, menu->buttons[5].pos.y + menu->buttons[5].height * 0.5);
	center(menu->text_level_6);
	menu->text_level_7 = mlx_put_string(cub3d->mlx, "Level 7", menu->buttons[6].pos.x + menu->buttons[6].width * 0.5, menu->buttons[6].pos.y + menu->buttons[6].height * 0.5);
	center(menu->text_level_7);
	menu->text_level_8 = mlx_put_string(cub3d->mlx, "Level 8", menu->buttons[7].pos.x + menu->buttons[7].width * 0.5, menu->buttons[7].pos.y + menu->buttons[7].height * 0.5);
	center(menu->text_level_8);
	menu->text_back = mlx_put_string(cub3d->mlx, "<-", menu->button_back.pos.x + menu->button_back.width * 0.5, menu->button_back.pos.y + menu->button_back.height * 0.5);
	center(menu->text_back);
	menu->text_leaderboard = mlx_put_string(cub3d->mlx, "Leaderboard", menu->button_leaderboard.pos.x + menu->button_leaderboard.width * 0.5, menu->button_leaderboard.pos.y + menu->button_leaderboard.height * 0.5);
	center(menu->text_leaderboard);

	disable_level_menu(menu);
}
