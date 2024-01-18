/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:00:08 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:11:46 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	set_positions_rest(t_start_menu *menu)
{
	int		exit_x;
	int		start_x;
	int		button_y;

	button_y = menu->img->height * 0.7;
	exit_x = menu->img->width * 0.35;
	start_x = menu->img->width * 0.5;
	menu->exit.pos.x = exit_x - menu->exit.img->width * 0.5;
	menu->exit.pos.y = button_y;
	menu->start_hover.pos.x = start_x - menu->start_hover.img->width * 0.5;
	menu->start_hover.pos.y = button_y;
	menu->exit_hover.pos.x = exit_x - menu->exit_hover.img->width * 0.5;
	menu->exit_hover.pos.y = button_y;
	menu->start.pos.x = start_x - menu->start.img->width * 0.5;
	menu->start.pos.y = button_y;
}

static void	set_positions(t_start_menu *menu)
{
	int		level_x;
	int		button_y;
	int		arrow_y;

	level_x = menu->img->width * 0.65;
	button_y = menu->img->height * 0.7;
	arrow_y = button_y + menu->exit.img->height
		* 0.5 - menu->arrow_exit.img->height * 0.5;
	menu->title.pos.x = menu->img->width * 0.5 - menu->title.img->width * 0.5;
	menu->title.pos.y = menu->img->height * 0.3;
	menu->level.pos.x = level_x - menu->level.img->width * 0.5;
	menu->level.pos.y = button_y;
	menu->level_hover.pos.x = level_x - menu->level_hover.img->width * 0.5;
	menu->level_hover.pos.y = button_y;
	menu->arrow_exit.pos.x = menu->exit.pos.x
		- menu->arrow_exit.img->width * 1.5;
	menu->arrow_exit.pos.y = arrow_y;
	menu->arrow_start.pos.x = menu->start.pos.x
		- menu->arrow_start.img->width * 1.5;
	menu->arrow_start.pos.y = arrow_y;
	menu->arrow_level.pos.x = menu->level.pos.x
		- menu->arrow_level.img->width * 1.5;
	menu->arrow_level.pos.y = arrow_y;
	set_positions_rest(menu);
}

static int	put_rest_images_to_window(mlx_t *mlx, t_start_menu *menu)
{
	if (mlx_image_to_window(mlx, menu->start_hover.img, menu->start_hover.pos.x,
			menu->start_hover.pos.y) < 0)
		return (err("Failed to put start menu start hover image to window"));
	if (mlx_image_to_window(mlx, menu->level_hover.img, menu->level_hover.pos.x,
			menu->level_hover.pos.y) < 0)
		return (err("Failed to put start menu level hover image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_exit.img, menu->arrow_exit.pos.x,
			menu->arrow_exit.pos.y) < 0)
		return (err("Failed to put start menu arrow exit image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_start.img, menu->arrow_start.pos.x,
			menu->arrow_start.pos.y) < 0)
		return (err("Failed to put start menu arrow start image to window"));
	if (mlx_image_to_window(mlx, menu->arrow_level.img, menu->arrow_level.pos.x,
			menu->arrow_level.pos.y) < 0)
		return (err("Failed to put start menu arrow level image to window"));
	return (1);
}

static int	put_images_to_window(mlx_t *mlx, t_start_menu *menu)
{
	if (mlx_image_to_window(mlx, menu->img, 0, 0) < 0)
		return (err("Failed to put start menu image to window"));
	if (mlx_image_to_window(mlx, menu->title.img, menu->title.pos.x,
			menu->title.pos.y) < 0)
		return (err("Failed to put start menu title image to window"));
	if (mlx_image_to_window(mlx, menu->exit.img, menu->exit.pos.x,
			menu->exit.pos.y) < 0)
		return (err("Failed to put start menu exit image to window"));
	if (mlx_image_to_window(mlx, menu->start.img, menu->start.pos.x,
			menu->start.pos.y) < 0)
		return (err("Failed to put start menu start image to window"));
	if (mlx_image_to_window(mlx, menu->level.img, menu->level.pos.x,
			menu->level.pos.y) < 0)
		return (err("Failed to put start menu level image to window"));
	if (mlx_image_to_window(mlx, menu->exit_hover.img, menu->exit_hover.pos.x,
			menu->exit_hover.pos.y) < 0)
		return (err("Failed to put start menu exit hover image to window"));
	if (!put_rest_images_to_window(mlx, menu))
		return (FAIL);
	return (SUCCESS);
}

int	init_start_menu(t_cub3d *cub3d, t_start_menu *menu)
{
	if (!load_png_start_menu(menu))
		return (FAIL);
	if (!init_images_start_menu(cub3d->mlx, menu))
	{
		free_prev_start_menu(menu, 9);
		return (FAIL);
	}
	set_positions(menu);
	draw_background(menu->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->img);
	if (!put_images_to_window(cub3d->mlx, menu))
	{
		free_prev_start_menu(menu, 9);
		return (FAIL);
	}
	disable_start_menu(menu);
	return (SUCCESS);
}
