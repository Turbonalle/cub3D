/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_additional_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:26:53 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:27:40 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	load_png_helper(t_level_menu *menu)
{
	const char	*number_png[LEVELS];
	int			i;

	number_png[0] = NUM_1_PNG;
	number_png[1] = NUM_2_PNG;
	number_png[2] = NUM_3_PNG;
	number_png[3] = NUM_4_PNG;
	number_png[4] = NUM_5_PNG;
	number_png[5] = NUM_6_PNG;
	number_png[6] = NUM_7_PNG;
	number_png[7] = NUM_8_PNG;
	i = -1;
	while (++i < LEVELS)
	{
		menu->minilevels[i].number.texture = mlx_load_png(number_png[i]);
		if (!menu->minilevels[i].number.texture)
			return (free_prev_level_menu(menu, i, 4));
	}
	return (SUCCESS);
}

int	load_png_level(t_level_menu *menu)
{
	menu->title.texture = mlx_load_png(LEVEL_TITLE_PNG);
	if (!menu->title.texture)
		return (FAIL);
	menu->back.texture = mlx_load_png(BACK_PNG);
	if (!menu->back.texture)
		return (free_prev_level_menu(menu, 0, 0));
	menu->back_hover.texture = mlx_load_png(BACK_HOVER_PNG);
	if (!menu->back.texture)
		return (free_prev_level_menu(menu, 0, 1));
	menu->leaderboard.texture = mlx_load_png(LEADERBOARD_PNG);
	if (!menu->back.texture)
		return (free_prev_level_menu(menu, 0, 2));
	menu->leaderboard_hover.texture = mlx_load_png(LEADERBOARD_HOVER_PNG);
	if (!menu->back.texture)
		return (free_prev_level_menu(menu, 0, 3));
	return (load_png_helper(menu));
}

static int	images_helper(mlx_t *mlx, t_level_menu *menu)
{
	int	size;
	int	i;

	i = -1;
	while (++i < LEVELS)
	{
		size = min(mlx->width * 0.15, mlx->height * 0.25);
		menu->minilevels[i].img = mlx_new_image(mlx, size, size);
		if (!menu->minilevels[i].img)
			return (err("Failed to create level menu minilevel image"));
		menu->minilevels[i].border = mlx_new_image(mlx, size
				+ MINILEVEL_BORDER_THICKNESS * 2,
				size + MINILEVEL_BORDER_THICKNESS * 2);
		if (!menu->minilevels[i].border)
			return (err("Failed to create level menu minilevel border image"));
		menu->minilevels[i].number.img
			= mlx_texture_to_image(mlx, menu->minilevels[i].number.texture);
		if (!menu->minilevels[i].number.img)
			return (err("Failed to create level menu minilevel number image"));
	}
	return (SUCCESS);
}

int	init_images_level(mlx_t *mlx, t_level_menu *menu)
{
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
	menu->leaderboard.img
		= mlx_texture_to_image(mlx, menu->leaderboard.texture);
	if (!menu->leaderboard.img)
		return (err("Failed to create level menu leaderboard image"));
	menu->leaderboard_hover.img
		= mlx_texture_to_image(mlx, menu->leaderboard_hover.texture);
	if (!menu->leaderboard_hover.img)
		return (err("Failed to create level menu leaderboard hover image"));
	return (images_helper(mlx, menu));
}

void	draw_minimap_preview(t_minilevel *minilevel, t_level *level)
{
	draw_background(minilevel->img, MINILEVEL_BG_COLOR);
	set_preview_values(minilevel, level);
	set_number_values(minilevel);
	draw_preview_map(minilevel, level, level->backup);
	draw_rectangle(minilevel->img, &minilevel->number_rect);
}
