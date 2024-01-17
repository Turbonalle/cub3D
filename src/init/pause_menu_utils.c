/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_menu_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:05:33 by slampine          #+#    #+#             */
/*   Updated: 2024/01/17 11:41:11 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	load_png_pause_menu(pause_menu_t *menu)
{
	menu->title.texture = mlx_load_png(PAUSE_PNG);
	if (!menu->title.texture)
		return (0);
	return (1);
}

int	init_images_pause_menu(mlx_t *mlx, pause_menu_t *menu)
{
	menu->bg = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!menu->bg)
		return (err("Failed to create image"));
	menu->menu = mlx_new_image(mlx, mlx->width * 0.5, mlx->height * 0.9);
	if (!menu->menu)
		return (err("Failed to create image"));
	menu->title.img = mlx_texture_to_image(mlx, menu->title.texture);
	if (!menu->title.img)
		return (err("Failed to create image"));
	return (SUCCESS);
}

int	init_sensitivity_slider(cub3d_t *cub3d, pause_menu_t *menu)
{
	menu->sensitivity_slider.pos.x = menu->pos_col_box_1;
	menu->sensitivity_slider.pos.y = menu->pos_row_4 + menu->box_fps[0].size
		* 0.5 - SLIDER_LINE_WIDTH * 0.5;
	menu->sensitivity_slider.length = menu->pos_col_box_4 - menu->pos_col_box_1
		+ menu->box_fps[0].size;
	menu->sensitivity_slider.value = MOUSE_SENSITIVITY;
	menu->sensitivity_slider.on_marker = FALSE;
	menu->sensitivity_slider.marker_min_pos = menu->sensitivity_slider.pos.x
		+ SLIDER_LINE_WIDTH;
	menu->sensitivity_slider.marker_max_pos = menu->sensitivity_slider.pos.x
		+ menu->sensitivity_slider.length - SLIDER_LINE_WIDTH;
	menu->sensitivity_slider.marker = mlx_new_image(cub3d->mlx,
			SLIDER_MARKER_WIDTH, SLIDER_MARKER_HEIGHT);
	if (!menu->sensitivity_slider.marker)
		return (err("Failed to create image"));
	menu->sensitivity_slider.marker_pos.x = get_marker_pos(cub3d);
	menu->sensitivity_slider.marker_pos.y = menu->sensitivity_slider.pos.y
		+ SLIDER_LINE_WIDTH / 2 - SLIDER_MARKER_HEIGHT / 2;
	if (mlx_image_to_window(cub3d->mlx, menu->sensitivity_slider.marker,
			menu->sensitivity_slider.marker_pos.x,
			menu->sensitivity_slider.marker_pos.y) < 0)
		return (err("Failed to put image to window"));
	return (SUCCESS);
}

void	init_settings(settings_t *settings)
{
	settings->e_speed = 0;
	settings->e_behaviour = 0;
	settings->fps = FPS_60;
	settings->fisheye = FALSE;
	settings->mouse = TRUE;
	settings->mouse_sensitivity = MOUSE_SENSITIVITY;
}
