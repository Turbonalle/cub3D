/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_level_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:26:56 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 11:41:35 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	set_positions_rest(level_menu_t *menu, vector_t *back_button_pos,
	int gap, vector_t coord)
{
	int			i;
	int			size;
	int			number_square_size;

	i = -1;
	size = menu->minilevels[0].img->width;
	number_square_size = size * 0.15;
	while (++i < LEVELS)
	{
		menu->minilevels[i].size = size;
		menu->minilevels[i].pos.x = back_button_pos->x + (i % coord.x)
			* (size + gap);
		menu->minilevels[i].pos.y = menu->img->height * 0.32 + (i / coord.x)
			* (size + gap);
		menu->minilevels[i].number.pos.x = menu->minilevels[i].pos.x
			+ number_square_size / 2
			- menu->minilevels[i].number.img->width / 2;
		menu->minilevels[i].number.pos.y = menu->minilevels[i].pos.y
			+ number_square_size / 2
			- menu->minilevels[i].number.img->height / 2;
	}
}

static void	set_positions(level_menu_t *menu, vector_t *back_button_pos)
{
	int			size;
	int			gap;
	int			number_square_size;
	vector_t	coord;

	menu->title.pos.x = (menu->img->width - menu->title.img->width) / 2;
	menu->title.pos.y = menu->img->height * 0.12;
	size = menu->minilevels[0].img->width;
	coord.y = 2;
	coord.x = LEVELS / coord.y + 1;
	if (LEVELS % coord.y == 0)
		coord.x = LEVELS / coord.y;
	gap = min(menu->img->width * 0.05, menu->img->height * 0.05);
	if (gap < MINILEVEL_BORDER_THICKNESS)
		gap = MINILEVEL_BORDER_THICKNESS;
	back_button_pos->x = (menu->img->width
			- (coord.x * size + (coord.x - 1) * gap)) / 2;
	back_button_pos->y = menu->img->height * 0.12;
	number_square_size = size * 0.15;
	menu->back.pos.x = back_button_pos->x;
	menu->back.pos.y = back_button_pos->y;
	menu->leaderboard.pos.x = menu->img->width
		- back_button_pos->x - menu->leaderboard.img->width;
	menu->leaderboard.pos.y = menu->img->height * 0.12;
	set_positions_rest(menu, back_button_pos, gap, coord);
}

static int	put_rest_images_to_window(mlx_t *mlx, level_menu_t *menu)
{
	int	i;

	i = -1;
	while (++i < LEVELS)
	{
		if (mlx_image_to_window(mlx, menu->minilevels[i].img,
				menu->minilevels[i].pos.x, menu->minilevels[i].pos.y) < 0)
			return (err("Failed to put level menu minilevel image to window"));
		if (mlx_image_to_window(mlx, menu->minilevels[i].number.img,
				menu->minilevels[i].number.pos.x,
				menu->minilevels[i].number.pos.y) < 0)
			return (err("Failed to put minilevel number image to window"));
		if (mlx_image_to_window(mlx, menu->minilevels[i].border,
				menu->minilevels[i].pos.x - MINILEVEL_BORDER_THICKNESS,
				menu->minilevels[i].pos.y - MINILEVEL_BORDER_THICKNESS) < 0)
			return (err("Failed to put minilevel border image to window"));
	}
	return (SUCCESS);
}

static int	put_images_to_window(mlx_t *mlx, level_menu_t *menu)
{
	if (mlx_image_to_window(mlx, menu->img, 0, 0) < 0)
		return (err("Failed to put level menu image to window"));
	if (mlx_image_to_window(mlx, menu->title.img,
			menu->title.pos.x, menu->title.pos.y) < 0)
		return (err("Failed to put level menu title image to window"));
	if (mlx_image_to_window(mlx, menu->back.img,
			menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put level menu back image to window"));
	if (mlx_image_to_window(mlx, menu->back_hover.img,
			menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put level menu back hover image to window"));
	if (mlx_image_to_window(mlx, menu->leaderboard.img,
			menu->leaderboard.pos.x, menu->leaderboard.pos.y) < 0)
		return (err("Failed to put level menu leaderboard image to window"));
	if (mlx_image_to_window(mlx, menu->leaderboard_hover.img,
			menu->leaderboard.pos.x, menu->leaderboard.pos.y) < 0)
		return (err("Failed to put leaderboard hover image to window"));
	return (put_rest_images_to_window(mlx, menu));
}

int	init_level_menu(cub3d_t *cub3d, level_menu_t *menu)
{
	int	i;

	if (!load_png_level(menu))
		return (FAIL);
	if (!init_images_level(cub3d->mlx, menu))
	{
		return (free_prev_level_menu(menu, LEVELS, 4));
	}
	set_positions(menu, &cub3d->back_button_pos);
	draw_background(menu->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->img);
	i = -1;
	while (++i < LEVELS)
	{
		printf("drawing minimap preview %d\n", i);
		draw_minimap_preview(&menu->minilevels[i], &cub3d->levels[i + 1]);
		draw_border_image(&menu->minilevels[i]);
	}
	printf("putting images to window\n");
	if (!put_images_to_window(cub3d->mlx, menu))
		return (FAIL);
	printf("disabling level menu\n");
	disable_level_menu(menu);
	printf("init level menu: done\n");
	return (SUCCESS);
}
