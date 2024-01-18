/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_menu_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:51:19 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	free_prev_start_menu(t_start_menu *menu, int i)
{
	mlx_delete_texture(menu->title.texture);
	if (i > 0)
		mlx_delete_texture(menu->exit.texture);
	if (i > 1)
		mlx_delete_texture(menu->exit_hover.texture);
	if (i > 2)
		mlx_delete_texture(menu->start.texture);
	if (i > 3)
		mlx_delete_texture(menu->start_hover.texture);
	if (i > 4)
		mlx_delete_texture(menu->level.texture);
	if (i > 5)
		mlx_delete_texture(menu->level_hover.texture);
	if (i > 6)
		mlx_delete_texture(menu->arrow_exit.texture);
	if (i > 7)
		mlx_delete_texture(menu->arrow_start.texture);
	if (i > 8)
		mlx_delete_texture(menu->arrow_level.texture);
	return (FAIL);
}

static int	load_png_rest(t_start_menu *menu)
{
	menu->arrow_exit.texture = mlx_load_png(ARROW_PNG);
	if (!menu->arrow_exit.texture)
		return (free_prev_start_menu(menu, 6));
	menu->arrow_start.texture = mlx_load_png(ARROW_PNG);
	if (!menu->arrow_start.texture)
		return (free_prev_start_menu(menu, 7));
	menu->arrow_level.texture = mlx_load_png(ARROW_PNG);
	if (!menu->arrow_level.texture)
		return (free_prev_start_menu(menu, 8));
	return (SUCCESS);
}

int	load_png_start_menu(t_start_menu *menu)
{
	menu->title.texture = mlx_load_png(START_TITLE_PNG);
	if (!menu->title.texture)
		return (FAIL);
	menu->exit.texture = mlx_load_png(START_EXIT_PNG);
	if (!menu->exit.texture)
		return (free_prev_start_menu(menu, 0));
	menu->exit_hover.texture = mlx_load_png(START_EXIT_HOVER_PNG);
	if (!menu->exit_hover.texture)
		return (free_prev_start_menu(menu, 1));
	menu->start.texture = mlx_load_png(START_START_PNG);
	if (!menu->start.texture)
		return (free_prev_start_menu(menu, 2));
	menu->start_hover.texture = mlx_load_png(START_START_HOVER_PNG);
	if (!menu->start_hover.texture)
		return (free_prev_start_menu(menu, 3));
	menu->level.texture = mlx_load_png(START_LEVEL_PNG);
	if (!menu->level.texture)
		return (free_prev_start_menu(menu, 4));
	menu->level_hover.texture = mlx_load_png(START_LEVEL_HOVER_PNG);
	if (!menu->level_hover.texture)
		return (free_prev_start_menu(menu, 5));
	return (load_png_rest(menu));
}

static int	init_images_rest(mlx_t *mlx, t_start_menu *menu)
{
	menu->level_hover.img
		= mlx_texture_to_image(mlx, menu->level_hover.texture);
	if (!menu->level_hover.img)
		return (err("Failed to create start menu level hover image"));
	menu->arrow_exit.img
		= mlx_texture_to_image(mlx, menu->arrow_exit.texture);
	if (!menu->arrow_exit.img)
		return (err("Failed to create start menu arrow exit image"));
	menu->arrow_start.img
		= mlx_texture_to_image(mlx, menu->arrow_start.texture);
	if (!menu->arrow_start.img)
		return (err("Failed to create start menu arrow start image"));
	menu->arrow_level.img
		= mlx_texture_to_image(mlx, menu->arrow_level.texture);
	if (!menu->arrow_level.img)
		return (err("Failed to create start menu arrow level image"));
	return (SUCCESS);
}

int	init_images_start_menu(mlx_t *mlx, t_start_menu *menu)
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
	menu->start_hover.img
		= mlx_texture_to_image(mlx, menu->start_hover.texture);
	if (!menu->start_hover.img)
		return (err("Failed to create start menu start hover image"));
	menu->level.img = mlx_texture_to_image(mlx, menu->level.texture);
	if (!menu->level.img)
		return (err("Failed to create start menu level image"));
	init_images_rest(mlx, menu);
	return (SUCCESS);
}
