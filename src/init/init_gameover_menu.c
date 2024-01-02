#include "../incl/cub3d.h"

static void	init_exit_button(cub3d_t *cub3d, button_t *button)
{
	button->width = cub3d->img->width * 0.2;
	button->height = button->width * 0.3;
	button->pos.x = cub3d->img->width * 0.5 - button->width / 2;
	button->pos.y = cub3d->img->height * 0.7;
	button->background_color = BUTTON_COLOR;
	button->border_color = BUTTON_BORDER_COLOR;
	button->border_width = BUTTON_BORDER_THICKNESS;
	button->state = FALSE;
}

static void	init_restart_button(cub3d_t *cub3d, button_t *button)
{
	button->width = cub3d->img->width * 0.2;
	button->height = button->width * 0.3;
	button->pos.x = cub3d->img->width * 0.5 - button->width / 2;
	button->pos.y = cub3d->img->height * 0.5;
	button->background_color = BUTTON_COLOR;
	button->border_color = BUTTON_BORDER_COLOR;
	button->border_width = BUTTON_BORDER_THICKNESS;
	button->state = FALSE;
}

static void	init_images(cub3d_t *cub3d, gameover_menu_t *menu)
{
	vector_t	title_pos;

	title_pos.x = cub3d->img->width * 0.5;
	title_pos.y = cub3d->img->height * 0.3;
	menu->text_gameover = mlx_put_string(cub3d->mlx, "Game Over", title_pos.x, title_pos.y);
	center(menu->text_gameover);
	menu->button_exit.text = mlx_put_string(cub3d->mlx, "Exit", menu->button_exit.pos.x + menu->button_exit.width / 2, menu->button_exit.pos.y + menu->button_exit.height / 2);
	center(menu->button_exit.text);
	menu->button_restart.text = mlx_put_string(cub3d->mlx, "Restart", menu->button_restart.pos.x + menu->button_restart.width / 2, menu->button_restart.pos.y + menu->button_restart.height / 2);
	center(menu->button_restart.text);
}

void	init_gameover_menu(cub3d_t *cub3d, gameover_menu_t *menu)
{
	menu->background_color = BLACK;
	init_exit_button(cub3d, &menu->button_exit);
	init_restart_button(cub3d, &menu->button_restart);
	menu->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
	if (!menu->img)
		err("Failed to create image");
	draw_menu_background(menu->img, menu->background_color);
	draw_button(menu->img, &menu->button_exit);
	draw_button(menu->img, &menu->button_restart);
	mlx_image_to_window(cub3d->mlx, menu->img, 0, 0);
	init_images(cub3d, menu);
	disable_gameover_menu(menu);
}