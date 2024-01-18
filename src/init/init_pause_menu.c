/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pause_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:29:57 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:52:09 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	set_positions(t_pause_menu *menu)
{
	int	gap_x;
	int	gap_y;

	gap_x = menu->menu->width * 0.10;
	gap_y = menu->menu->height * 0.13;
	menu->menu_pos.x = (menu->bg->width - menu->menu->width) / 2;
	menu->menu_pos.y = (menu->bg->height - menu->menu->height) / 2;
	menu->title.pos.x = menu->menu_pos.x
		+ (menu->menu->width - menu->title.img->width) / 2;
	menu->title.pos.y = menu->menu_pos.y + menu->menu->height * 0.15;
	menu->pos_col_text = menu->menu_pos.x + menu->menu->width * 0.15;
	menu->pos_col_box_1 = menu->menu_pos.x + menu->menu->width * 0.38;
	menu->pos_col_box_2 = menu->pos_col_box_1 + gap_x;
	menu->pos_col_box_3 = menu->pos_col_box_2 + gap_x;
	menu->pos_col_box_4 = menu->pos_col_box_3 + gap_x;
	menu->pos_col_box_5 = menu->pos_col_box_4 + gap_x;
	menu->pos_row_1 = menu->menu_pos.y + menu->menu->height * 0.4;
	menu->pos_row_2 = menu->pos_row_1 + gap_y;
	menu->pos_row_3 = menu->pos_row_2 + gap_y;
	menu->pos_row_4 = menu->pos_row_3 + gap_y;
}

static int	put_images_to_window(mlx_t *mlx, t_pause_menu *menu)
{
	if (mlx_image_to_window(mlx, menu->bg, 0, 0) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->menu, menu->menu_pos.x,
			menu->menu_pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(mlx, menu->title.img, menu->title.pos.x,
			menu->title.pos.y) < 0)
		return (err("Failed to put image to window"));
	return (SUCCESS);
}

void	draw_pause(t_cub3d *cub3d, t_pause_menu *menu)
{
	update_settings(cub3d, menu);
	draw_background(menu->bg, set_transparency(PAUSE_MENU_BACKGROUND_COLOR,
			PAUSE_MENU_TRANSPARENCY));
	draw_background(menu->menu, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->menu);
	draw_slider(menu->menu, &menu->sensitivity_slider);
	add_category_text(cub3d, menu);
	add_checkbox_text(cub3d, menu);
	disable_pause_menu(cub3d->mlx, menu);
}

int	init_pause_menu(t_cub3d *cub3d, t_pause_menu *menu)
{
	if (!load_png_pause_menu(menu))
		return (0);
	if (!init_images_pause_menu(cub3d->mlx, menu))
	{
		mlx_delete_texture(menu->title.texture);
		return (FAIL);
	}
	set_positions(menu);
	init_checkboxes(menu);
	set_checkbox_values(menu);
	init_checkbox_states(menu);
	init_settings(&cub3d->settings);
	if (!put_images_to_window(cub3d->mlx, menu))
	{
		mlx_delete_texture(menu->title.texture);
		return (FAIL);
	}
	if (!init_sensitivity_slider(cub3d, menu))
	{
		mlx_delete_texture(menu->title.texture);
		return (FAIL);
	}
	draw_pause(cub3d, menu);
	return (SUCCESS);
}
