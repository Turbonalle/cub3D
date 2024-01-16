/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_name_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:17:58 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 15:31:38 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	load_png(name_menu_t *menu)
{
	menu->title_win.texture = mlx_load_png(GAMEOVER_WIN_PNG);
	if (!menu->title_win.texture)
		return (FAIL);
	menu->title_top3.texture = mlx_load_png(TOP3_PNG);
	if (!menu->title_top3.texture)
		return (FAIL);
	menu->timer.texture = mlx_load_png(TIMER_PNG);
	if (!menu->timer.texture)
		return (0);
	menu->back.texture = mlx_load_png(BACK_PNG);
	if (!menu->back.texture)
		return (free_prev_name_menu(menu, 0));
	menu->back_hover.texture = mlx_load_png(BACK_HOVER_PNG);
	if (!menu->back_hover.texture)
		return (free_prev_name_menu(menu, 1));
	return (1);
}

static int	init_images(mlx_t *mlx, name_menu_t *menu)
{
	menu->img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!menu->img)
		return (err("Failed to create name menu image"));
	menu->title_win.img = mlx_texture_to_image(mlx, menu->title_win.texture);
	if (!menu->title_win.img)
		return (err("Failed to create name menu title win image"));
	menu->title_top3.img = mlx_texture_to_image(mlx, menu->title_top3.texture);
	if (!menu->title_top3.img)
		return (err("Failed to create name menu title top 3 image"));
	menu->back.img = mlx_texture_to_image(mlx, menu->back.texture);
	if (!menu->back.img)
		return (err("Failed to create name menu back image"));
	menu->back_hover.img = mlx_texture_to_image(mlx, menu->back_hover.texture);
	if (!menu->back_hover.img)
		return (err("Failed to create name menu back hover image"));
	menu->timer.img = mlx_texture_to_image(mlx, menu->timer.texture);
	if (!menu->timer.img)
		return (err("Failed to create timer image"));
	return (SUCCESS);
}

static void	set_positions(name_menu_t *menu, vector_t back_button_pos)
{
	menu->title_win.pos.x = menu->img->width
		* 0.5 - menu->title_win.img->width * 0.5;
	menu->title_win.pos.y = menu->img->height * 0.12;
	menu->title_top3.pos.x = menu->img->width
		* 0.5 - menu->title_top3.img->width * 0.5;
	menu->title_top3.pos.y = menu->img->height * 0.3;
	menu->back.pos.x = back_button_pos.x;
	menu->back.pos.y = back_button_pos.y;
	menu->back_hover.pos.x = back_button_pos.x;
	menu->back_hover.pos.y = back_button_pos.y;
	menu->timer.pos.x = menu->img->width * 0.5
		- menu->timer.img->width * 0.5;
	menu->timer.pos.y = menu->img->height * 0.52
		- menu->timer.img->height * 0.5;
	menu->rect_input.width = menu->img->width * 0.6;
	menu->rect_input.height = (menu->rect_input.width
			- (NAME_BOX_GAP * (MAX_NAME_LENGTH - 1))) / MAX_NAME_LENGTH;
	menu->rect_input.pos.x = (menu->img->width - menu->rect_input.width) / 2;
	menu->rect_input.pos.y = menu->img->height * 0.7;
	menu->rect_input.color = WHITE;
	set_letter_fields(menu);
}

static int	put_images_to_window(mlx_t *mlx, name_menu_t *menu)
{
	if (mlx_image_to_window(mlx, menu->img, 0, 0) < 0)
		return (err("Failed to put name menu image to window"));
	if (mlx_image_to_window(mlx, menu->title_win.img,
			menu->title_win.pos.x, menu->title_win.pos.y) < 0)
		return (err("Failed to put name menu title win image to window"));
	if (mlx_image_to_window(mlx, menu->title_top3.img,
			menu->title_top3.pos.x, menu->title_top3.pos.y) < 0)
		return (err("Failed to put name menu title top 3 image to window"));
	if (mlx_image_to_window(mlx, menu->back.img,
			menu->back.pos.x, menu->back.pos.y) < 0)
		return (err("Failed to put name menu back image to window"));
	if (mlx_image_to_window(mlx, menu->back_hover.img,
			menu->back_hover.pos.x, menu->back_hover.pos.y) < 0)
		return (err("Failed to put name menu back hover image to window"));
	if (mlx_image_to_window(mlx, menu->timer.img,
			menu->timer.pos.x, menu->timer.pos.y) < 0)
		return (err("Failed to put timer image to window"));
	return (SUCCESS);
}

int	init_name_menu(cub3d_t *cub3d, name_menu_t *menu)
{
	int	i;

	if (!load_png(menu))
		return (FAIL);
	if (!init_images(cub3d->mlx, menu))
	{
		free_prev_name_menu(menu, 2);
		return (err("Failed to init name menu images"));
	}
	set_positions(menu, cub3d->back_button_pos);
	init_name_values(menu);
	draw_background(menu->img, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->img);
	i = -1;
	while (++i < MAX_NAME_LENGTH)
		draw_letter_box(menu->img, &menu->box[i]);
	if (!put_images_to_window(cub3d->mlx, menu))
	{
		free_prev_name_menu(menu, 2);
		return (0);
	}
	init_letter_images(cub3d, menu);
	disable_name_menu(cub3d->mlx, menu);
	return (SUCCESS);
}
