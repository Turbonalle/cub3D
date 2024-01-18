/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameover_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:16:12 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	load_png_rest(t_gameover_menu *menu)
{
	menu->restart_hover.texture = mlx_load_png(GAMEOVER_RESTART_HOVER_PNG);
	if (!menu->restart_hover.texture)
		return (free_prev_gameover_menu(menu, 5));
	menu->arrow_back.texture = mlx_load_png(ARROW_PNG);
	if (!menu->arrow_back.texture)
		return (free_prev_gameover_menu(menu, 6));
	menu->arrow_restart.texture = mlx_load_png(ARROW_PNG);
	if (!menu->arrow_restart.texture)
		return (free_prev_gameover_menu(menu, 7));
	return (SUCCESS);
}

int	load_png_gameover(t_gameover_menu *menu)
{
	menu->title_win.texture = mlx_load_png(GAMEOVER_WIN_PNG);
	if (!menu->title_win.texture)
		return (FAIL);
	menu->title_gameover.texture = mlx_load_png(GAMEOVER_GAMEOVER_PNG);
	if (!menu->title_gameover.texture)
		return (free_prev_gameover_menu(menu, 0));
	menu->timer.texture = mlx_load_png(TIMER_PNG);
	if (!menu->timer.texture)
		return (free_prev_gameover_menu(menu, 1));
	menu->back.texture = mlx_load_png(GAMEOVER_EXIT_PNG);
	if (!menu->back.texture)
		return (free_prev_gameover_menu(menu, 2));
	menu->back_hover.texture = mlx_load_png(GAMEOVER_EXIT_HOVER_PNG);
	if (!menu->back_hover.texture)
		return (free_prev_gameover_menu(menu, 3));
	menu->restart.texture = mlx_load_png(GAMEOVER_RESTART_PNG);
	if (!menu->restart.texture)
		return (free_prev_gameover_menu(menu, 4));
	if (!load_png_rest(menu))
		return (FAIL);
	return (SUCCESS);
}

static int	init_images_rest(mlx_t *mlx, t_gameover_menu *menu)
{
	menu->restart_hover.img = mlx_texture_to_image(mlx,
			menu->restart_hover.texture);
	if (!menu->restart_hover.img)
		return (err("Failed to create image"));
	menu->arrow_back.img = mlx_texture_to_image(mlx, menu->arrow_back.texture);
	if (!menu->arrow_back.img)
		return (err("Failed to create image"));
	menu->arrow_restart.img = mlx_texture_to_image(mlx,
			menu->arrow_restart.texture);
	if (!menu->arrow_restart.img)
		return (err("Failed to create image"));
	return (SUCCESS);
}

int	init_images_gameover(mlx_t *mlx, t_gameover_menu *menu)
{
	menu->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!menu->img)
		return (err("Failed to create image"));
	menu->title_win.img = mlx_texture_to_image(mlx, menu->title_win.texture);
	if (!menu->title_win.img)
		return (err("Failed to create image"));
	menu->title_gameover.img = mlx_texture_to_image(mlx,
			menu->title_gameover.texture);
	if (!menu->title_gameover.img)
		return (err("Failed to create image"));
	menu->timer.img = mlx_texture_to_image(mlx, menu->timer.texture);
	if (!menu->timer.img)
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
	if (!init_images_rest(mlx, menu))
		return (FAIL);
	return (SUCCESS);
}

int	free_prev_gameover_menu(t_gameover_menu *menu, int i)
{
	mlx_delete_texture(menu->title_win.texture);
	if (i > 0)
		mlx_delete_texture(menu->title_gameover.texture);
	if (i > 1)
		mlx_delete_texture(menu->timer.texture);
	if (i > 2)
		mlx_delete_texture(menu->back.texture);
	if (i > 3)
		mlx_delete_texture(menu->back_hover.texture);
	if (i > 4)
		mlx_delete_texture(menu->restart.texture);
	if (i > 5)
		mlx_delete_texture(menu->restart_hover.texture);
	if (i > 6)
		mlx_delete_texture(menu->arrow_back.texture);
	if (i > 7)
		mlx_delete_texture(menu->arrow_restart.texture);
	return (FAIL);
}
