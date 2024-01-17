/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gameover_menu.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:16:12 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 18:34:52 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"


static void	set_rest_positions(gameover_menu_t *menu)
{
	int	back_x;
	int	restart_x;
	int	button_y;
	int	gap;

	gap = menu->img->width * 0.07;
	back_x = (menu->img->width - menu->back.img->width - gap
			- menu->restart.img->width) / 2;
	restart_x = back_x + menu->back.img->width + gap;
	button_y = menu->img->height * 0.7;
	menu->arrow_back.pos.x = menu->back.pos.x
		- menu->arrow_back.img->width * 1.5;
	menu->arrow_back.pos.y = button_y + menu->back.img->height
		* 0.5 - menu->arrow_back.img->height * 0.5;
	menu->arrow_restart.pos.x = menu->restart.pos.x
		- menu->arrow_restart.img->width * 1.5;
	menu->arrow_restart.pos.y = button_y + menu->restart.img->height
		* 0.5 - menu->arrow_restart.img->height * 0.5;
	menu->restart.pos.x = restart_x;
	menu->restart.pos.y = button_y;
	menu->restart_hover.pos.x = restart_x;
	menu->restart_hover.pos.y = button_y;
}

static void	set_positions(gameover_menu_t *menu)
{
	int	back_x;
	int	restart_x;
	int	button_y;
	int	gap;

	gap = menu->img->width * 0.07;
	back_x = (menu->img->width - menu->back.img->width
			- gap - menu->restart.img->width) / 2;
	restart_x = back_x + menu->back.img->width + gap;
	button_y = menu->img->height * 0.7;
	menu->title_win.pos.x = menu->img->width * 0.5
		- menu->title_win.img->width * 0.5;
	menu->title_win.pos.y = menu->img->height * 0.3;
	menu->title_gameover.pos.x = menu->img->width * 0.5
		- menu->title_gameover.img->width * 0.5;
	menu->title_gameover.pos.y = menu->img->height * 0.3;
	menu->timer.pos.x = menu->img->width * 0.5 - menu->timer.img->width * 0.5;
	menu->timer.pos.y = menu->img->height * 0.53
		- menu->timer.img->height * 0.5;
	menu->back.pos.x = back_x;
	menu->back.pos.y = button_y;
	menu->back_hover.pos.x = back_x;
	menu->back_hover.pos.y = button_y;
	set_rest_positions(menu);
}

static int	put_rest_images_to_window(mlx_t *mlx, gameover_menu_t *menu)
{
	if (mlx_image_to_window(mlx, menu->restart_hover.img,
			menu->restart_hover.pos.x, menu->restart_hover.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_back.img,
			menu->arrow_back.pos.x, menu->arrow_back.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_restart.img,
			menu->arrow_restart.pos.x, menu->arrow_restart.pos.y) < 0)
		return (err("Failed to put image to window"));
	return (SUCCESS);
}

static int	put_images_to_window(mlx_t *mlx, gameover_menu_t *menu)
{
	if (mlx_image_to_window(mlx, menu->img, 0, 0) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->title_win.img,
			menu->title_win.pos.x, menu->title_win.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->title_gameover.img,
			menu->title_gameover.pos.x, menu->title_gameover.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->timer.img,
			menu->timer.pos.x, menu->timer.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->back.img,
			menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->back_hover.img,
			menu->back_hover.pos.x, menu->back_hover.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->restart.img,
			menu->restart.pos.x, menu->restart.pos.y) < 0)
		return (err("Failed to put image to window"));
	return (put_rest_images_to_window(mlx, menu));
}

int	init_gameover_menu(cub3d_t *cub3d, gameover_menu_t *menu)
{
	if (!load_png_gameover(menu))
		return (0);
	if (!init_images_gameover(cub3d->mlx, menu))
		return (FAIL);
	set_positions(menu);
	draw_background(menu->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->img);
	if (!put_images_to_window(cub3d->mlx, menu))
		return (FAIL);
	disable_gameover_menu(cub3d->mlx, menu);
	return (SUCCESS);
}