#include "../incl/cub3d.h"

static load_png(level_menu_t *menu)
{
	menu->title.texture = mlx_load_png(LEVEL_TITLE_PNG);
	menu->back.texture = mlx_load_png(LEVEL_BACK_PNG);
	menu->back_hover.texture = mlx_load_png(LEVEL_BACK_HOVER_PNG);
	menu->leaderboard.texture = mlx_load_png(LEVEL_LEADERBOARD_PNG);
	menu->leaderboard_hover.texture = mlx_load_png(LEVEL_LEADERBOARD_HOVER_PNG);
}

static int	init_images(mlx_t *mlx, level_menu_t *menu)
{
	int	i;

	menu->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!menu->img)
		return (err("Failed to create level menu image"));
	menu->title.img = mlx_texture_to_image(mlx, menu->title.texture);
	if (!menu->title.img)
		return (err("Failed to create level menu title image"));
	menu->back.img = mlx_texture_to_image(mlx, menu->back.texture);
	if (!menu->back.img)
		return (err("Failed to create level menu back image"));
	menu->back_hover.img = mlx_texture_to_image(mlx, menu->back_hover.texture);
	if (!menu->back_hover.img)
		return (err("Failed to create level menu back hover image"));
	// menu->leaderboard.img = mlx_texture_to_image(mlx, menu->leaderboard.texture);
	// if (!menu->leaderboard.img)
	// 	return (err("Failed to create level menu leaderboard image"));
	// menu->leaderboard_hover.img = mlx_texture_to_image(mlx, menu->leaderboard_hover.texture);
	// if (!menu->leaderboard_hover.img)
	// 	return (err("Failed to create level menu leaderboard hover image"));
	i = -1;
	while (++i < LEVELS)
	{
		menu->minilevels[i].img = mlx_new_image(mlx, mlx->width * 0.2, mlx->height * 0.15);
		if (!menu->minilevels[i].img)
			return (err("Failed to create level menu minilevel image"));
	}
	return (SUCCESS);
}

static void	set_positions(level_menu_t *menu)
{
	int	i;
	int	mini_width;
	int	mini_height;
	int	gap;

	menu->title.pos.x = (menu->img->width - menu->title.img->width) / 2;
	menu->title.pos.y = menu->img->height * 0.2;
	menu->back.pos.x = menu->img->width * 0.2;
	menu->back.pos.y = menu->img->height * 0.2;
	// menu->leaderboard.pos.x = menu->img->width * 0.8 - menu->leaderboard.img->width;
	// menu->leaderboard.pos.y = menu->img->height * 0.2;
	mini_width = menu->minilevels[0].img->width;
	i = -1;
	while (++i < LEVELS)
	{
		menu->minilevels[i].pos.x = menu->img->width * 0.2 + (i * menu->img->width * 0.2);
		menu->minilevels[i].pos.y = menu->img->height * 0.4 + (i * menu->img->height * 0.15);
	}
}

static int	put_images_to_window(mlx_t *mlx, level_menu_t *menu)
{
	int	i;

	if (mlx_image_to_window(mlx, menu->img, 0, 0) < 0)
		return (err("Failed to put level menu image to window"));
	if (mlx_image_to_image(mlx, menu->title.img, menu->title.pos.x, menu->title.pos.y) < 0)
		return (err("Failed to put level menu title image to window"));
	if (mlx_image_to_image(mlx, menu->back.img, menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put level menu back image to window"));
	if (mlx_image_to_image(mlx, menu->back_hover.img, menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put level menu back hover image to window"));
	// if (mlx_image_to_image(mlx, menu->leaderboard.img, menu->leaderboard.pos.x, menu->leaderboard.pos.y) < 0)
	// 	return (err("Failed to put level menu leaderboard image to window"));
	// if (mlx_image_to_image(mlx, menu->leaderboard_hover.img, menu->leaderboard.pos.x, menu->leaderboard.pos.y) < 0)
	// 	return (err("Failed to put level menu leaderboard hover image to window"));
	i = -1;
	while (++i < LEVELS)
	{
		if (mlx_image_to_image(mlx, menu->minilevels[i].img, menu->minilevels[i].pos.x, menu->minilevels[i].pos.y) < 0)
			return (err("Failed to put level menu minilevel image to window"));
	}
	return (SUCCESS);
}

int	init_level_menu(cub3d_t *cub3d, level_menu_t *menu)
{
	load_png(menu);
	if (!init_images(cub3d->mlx, menu))
		return (FAIL);
	set_positions(menu);
	draw_menu_background(menu->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->img);
	if (!put_images_to_window(cub3d->mlx, menu))
		return (FAIL);
	disable_level_menu(menu);
	return (SUCCESS);
}
