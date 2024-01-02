#include "../incl/cub3d.h"

static void load_png(gameover_menu_t *menu)
{
	menu->title_win.texture = mlx_load_png(GAMEOVER_WIN_PNG);
	menu->title_gameover.texture = mlx_load_png(GAMEOVER_GAMEOVER_PNG);
	menu->back.texture = mlx_load_png(GAMEOVER_EXIT_PNG);
	menu->back_hover.texture = mlx_load_png(GAMEOVER_EXIT_HOVER_PNG);
	menu->restart.texture = mlx_load_png(GAMEOVER_RESTART_PNG);
	menu->restart_hover.texture = mlx_load_png(GAMEOVER_RESTART_HOVER_PNG);
	menu->arrow_back.texture = mlx_load_png(ARROW_PNG);
	menu->arrow_restart.texture = mlx_load_png(ARROW_PNG);
}

static int init_images(mlx_t *mlx, gameover_menu_t *menu)
{
	menu->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!menu->img)
		return (err("Failed to create image"));
	menu->title_win.img = mlx_texture_to_image(mlx, menu->title_win.texture);
	if (!menu->title_win.img)
		return (err("Failed to create image"));
	menu->title_gameover.img = mlx_texture_to_image(mlx, menu->title_gameover.texture);
	if (!menu->title_gameover.img)
		return (err("Failed to create image"));
	menu->back.img = mlx_texture_to_image(mlx, menu->back.texture);
	if (!menu->back.img)
		return (err("Failed to create image"));
	menu->back_hover.img = mlx_texture_to_image(mlx, menu->back_hover.texture);
	if (!menu->back_hover.img)
		return (err("Failed to create image"));
	menu->restart.img = mlx_texture_to_image(mlx, menu->restart.texture);
	if (!menu->restart.img)
		return (err("Failed to create image"));
	menu->restart_hover.img = mlx_texture_to_image(mlx, menu->restart_hover.texture);
	if (!menu->restart_hover.img)
		return (err("Failed to create image"));
	menu->arrow_back.img = mlx_texture_to_image(mlx, menu->arrow_back.texture);
	if (!menu->arrow_back.img)
		return (err("Failed to create image"));
	menu->arrow_restart.img = mlx_texture_to_image(mlx, menu->arrow_restart.texture);
	if (!menu->arrow_restart.img)
		return (err("Failed to create image"));
	return (SUCCESS);
}

static void set_positions(gameover_menu_t *menu)
{
	int	back_x;
	int	restart_x;
	int	button_y;
	int	gap;

	gap = menu->img->width * 0.07;
	back_x = (menu->img->width - menu->back.img->width - gap - menu->restart.img->width) / 2;
	restart_x = back_x + menu->back.img->width + gap;
	button_y = menu->img->height * 0.7;
	menu->title_win.pos.x = menu->img->width * 0.5 - menu->title_win.img->width * 0.5;
	menu->title_win.pos.y = menu->img->height * 0.3;
	menu->title_gameover.pos.x = menu->img->width * 0.5 - menu->title_gameover.img->width * 0.5;
	menu->title_gameover.pos.y = menu->img->height * 0.3;
	menu->back.pos.x = back_x;
	menu->back.pos.y = button_y;
	menu->back_hover.pos.x = back_x;
	menu->back_hover.pos.y = button_y;
	menu->restart.pos.x = restart_x;
	menu->restart.pos.y = button_y;
	menu->restart_hover.pos.x = restart_x;
	menu->restart_hover.pos.y = button_y;
	menu->arrow_back.pos.x = menu->back.pos.x - menu->arrow_back.img->width * 1.5;
	menu->arrow_back.pos.y = button_y + menu->back.img->height * 0.5 - menu->arrow_back.img->height * 0.5;
	menu->arrow_restart.pos.x = menu->restart.pos.x - menu->arrow_restart.img->width * 1.5;
	menu->arrow_restart.pos.y = button_y + menu->restart.img->height * 0.5 - menu->arrow_restart.img->height * 0.5;
}

static int put_images_to_window(mlx_t *mlx, gameover_menu_t *menu)
{
	if (mlx_image_to_window(mlx, menu->img, 0, 0) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->title_win.img, menu->title_win.pos.x, menu->title_win.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->title_gameover.img, menu->title_gameover.pos.x, menu->title_gameover.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->back.img, menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->back_hover.img, menu->back_hover.pos.x, menu->back_hover.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->restart.img, menu->restart.pos.x, menu->restart.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->restart_hover.img, menu->restart_hover.pos.x, menu->restart_hover.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_back.img, menu->arrow_back.pos.x, menu->arrow_back.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_restart.img, menu->arrow_restart.pos.x, menu->arrow_restart.pos.y) < 0)
		return (err("Failed to put image to window"));
	return (SUCCESS);
}

int	init_gameover_menu(cub3d_t *cub3d, gameover_menu_t *menu)
{
	load_png(menu);
	if (!init_images(cub3d->mlx, menu))
		return (FAIL);
	set_positions(menu);
	draw_menu_background(menu->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->img);
	if (!put_images_to_window(cub3d->mlx, menu))
		return (FAIL);
	disable_gameover_menu(menu);
	return (SUCCESS);
}