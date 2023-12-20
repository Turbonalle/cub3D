#include "../incl/cub3d.h"

static void	load_png(start_menu_t *menu)
{
	menu->title.texture = mlx_load_png(START_TITLE_PNG);
	menu->exit.texture = mlx_load_png(START_EXIT_PNG);
	menu->exit_hover.texture = mlx_load_png(START_EXIT_HOVER_PNG);
	menu->start.texture = mlx_load_png(START_START_PNG);
	menu->start_hover.texture = mlx_load_png(START_START_HOVER_PNG);
	menu->level.texture = mlx_load_png(START_LEVEL_PNG);
	menu->level_hover.texture = mlx_load_png(START_LEVEL_HOVER_PNG);
	menu->arrow_exit.texture = mlx_load_png(START_ARROW_PNG);
	menu->arrow_start.texture = mlx_load_png(START_ARROW_PNG);
	menu->arrow_level.texture = mlx_load_png(START_ARROW_PNG);
}

static int	init_images(mlx_t *mlx, start_menu_t *menu)
{
	menu->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!menu->img)
		return (err("Failed to create start menu image"));
	menu->title.img = mlx_texture_to_image(mlx, menu->title.texture);
	if (!menu->title.img)
		return (err("Failed to create start menu title image"));
	menu->exit.img = mlx_texture_to_image(mlx, menu->exit.texture);
	if (!menu->exit.img)
		return (err("Failed to create start menu exit image"));
	menu->exit_hover.img = mlx_texture_to_image(mlx, menu->exit_hover.texture);
	if (!menu->exit_hover.img)
		return (err("Failed to create start menu exit hover image"));
	menu->start.img = mlx_texture_to_image(mlx, menu->start.texture);
	if (!menu->start.img)
		return (err("Failed to create start menu start image"));
	menu->start_hover.img = mlx_texture_to_image(mlx, menu->start_hover.texture);
	if (!menu->start_hover.img)
		return (err("Failed to create start menu start hover image"));
	menu->level.img = mlx_texture_to_image(mlx, menu->level.texture);
	if (!menu->level.img)
		return (err("Failed to create start menu level image"));
	menu->level_hover.img = mlx_texture_to_image(mlx, menu->level_hover.texture);
	if (!menu->level_hover.img)
		return (err("Failed to create start menu level hover image"));
	menu->arrow_exit.img = mlx_texture_to_image(mlx, menu->arrow_exit.texture);
	if (!menu->arrow_exit.img)
		return (err("Failed to create start menu arrow exit image"));
	menu->arrow_start.img = mlx_texture_to_image(mlx, menu->arrow_start.texture);
	if (!menu->arrow_start.img)
		return (err("Failed to create start menu arrow start image"));
	menu->arrow_level.img = mlx_texture_to_image(mlx, menu->arrow_level.texture);
	if (!menu->arrow_level.img)
		return (err("Failed to create start menu arrow level image"));
	return (SUCCESS);
}

static void	set_positions(start_menu_t *menu)
{
	int		exit_x;
	int		start_x;
	int		level_x;
	int		button_y;
	int		arrow_y;

	exit_x = menu->img->width * 0.35;
	start_x = menu->img->width * 0.5;
	level_x = menu->img->width * 0.65;
	button_y = menu->img->height * 0.7;
	arrow_y = button_y + menu->exit.img->height * 0.5 - menu->arrow_exit.img->height * 0.5;
	menu->title.pos.x = menu->img->width * 0.5 - menu->title.img->width * 0.5;
	menu->title.pos.y = menu->img->height * 0.3;
	menu->exit.pos.x = exit_x - menu->exit.img->width * 0.5;
	menu->exit.pos.y = button_y;
	menu->exit_hover.pos.x = exit_x - menu->exit_hover.img->width * 0.5;
	menu->exit_hover.pos.y = button_y;
	menu->start.pos.x = start_x - menu->start.img->width * 0.5;
	menu->start.pos.y = button_y;
	menu->start_hover.pos.x = start_x - menu->start_hover.img->width * 0.5;
	menu->start_hover.pos.y = button_y;
	menu->level.pos.x = level_x - menu->level.img->width * 0.5;
	menu->level.pos.y = button_y;
	menu->level_hover.pos.x = level_x - menu->level_hover.img->width * 0.5;
	menu->level_hover.pos.y = button_y;
	menu->arrow_exit.pos.x = menu->exit.pos.x - menu->arrow_exit.img->width * 1.5;
	menu->arrow_exit.pos.y = arrow_y;
	menu->arrow_start.pos.x = menu->start.pos.x - menu->arrow_start.img->width * 1.5;
	menu->arrow_start.pos.y = arrow_y;
	menu->arrow_level.pos.x = menu->level.pos.x - menu->arrow_level.img->width * 1.5;
	menu->arrow_level.pos.y = arrow_y;
}

static int	put_images_to_window(mlx_t *mlx, start_menu_t *menu)
{
	if (mlx_image_to_window(mlx, menu->img, 0, 0) < 0)
		return (err("Failed to put start menu image to window"));
	if (mlx_image_to_window(mlx, menu->title.img, menu->title.pos.x, menu->title.pos.y) < 0)
		return (err("Failed to put start menu title image to window"));
	if (mlx_image_to_window(mlx, menu->exit.img, menu->exit.pos.x, menu->exit.pos.y) < 0)
		return (err("Failed to put start menu exit image to window"));
	if (mlx_image_to_window(mlx, menu->start.img, menu->start.pos.x, menu->start.pos.y) < 0)
		return (err("Failed to put start menu start image to window"));
	if (mlx_image_to_window(mlx, menu->level.img, menu->level.pos.x, menu->level.pos.y) < 0)
		return (err("Failed to put start menu level image to window"));
	if (mlx_image_to_window(mlx, menu->exit_hover.img, menu->exit_hover.pos.x, menu->exit_hover.pos.y) < 0)
		return (err("Failed to put start menu exit hover image to window"));
	if (mlx_image_to_window(mlx, menu->start_hover.img, menu->start_hover.pos.x, menu->start_hover.pos.y) < 0)
		return (err("Failed to put start menu start hover image to window"));
	if (mlx_image_to_window(mlx, menu->level_hover.img, menu->level_hover.pos.x, menu->level_hover.pos.y) < 0)
		return (err("Failed to put start menu level hover image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_exit.img, menu->arrow_exit.pos.x, menu->arrow_exit.pos.y) < 0)
		return (err("Failed to put start menu arrow exit image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_start.img, menu->arrow_start.pos.x, menu->arrow_start.pos.y) < 0)
		return (err("Failed to put start menu arrow start image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_level.img, menu->arrow_level.pos.x, menu->arrow_level.pos.y) < 0)
		return (err("Failed to put start menu arrow level image to window"));
	return (SUCCESS);
}

int	init_start_menu(cub3d_t *cub3d, start_menu_t *menu)
{
	printf("Initializing start menu...\n");
	load_png(menu);
	if (!init_images(cub3d->mlx, menu))
		return (FAIL);
	set_positions(menu);
	draw_menu_background(menu->img, START_MENU_BACKGROUND_COLOR);
	draw_start_menu_border(menu->img);
	if (!put_images_to_window(cub3d->mlx, menu))
		return (FAIL);
	printf("Start menu initialized\n");
	return (SUCCESS);
}
