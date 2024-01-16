/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_pause_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:49:00 by slampine          #+#    #+#             */
/*   Updated: 2024/01/16 16:35:58 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	get_marker_pos(cub3d_t *cub3d)
{
	range_t	marker_range;
	range_t	sensitivity_range;

	marker_range.start = cub3d->pause_menu.sensitivity_slider.marker_min_pos;
	marker_range.end = cub3d->pause_menu.sensitivity_slider.marker_max_pos;
	sensitivity_range.start = MOUSE_MIN_SENSITIVITY;
	sensitivity_range.end = MOUSE_MAX_SENSITIVITY;
	return (lerp(marker_range, sensitivity_range,
			cub3d->settings.mouse_sensitivity) - SLIDER_MARKER_WIDTH / 2);
}

double	get_sensitivity(cub3d_t *cub3d)
{
	range_t	marker_range;
	range_t	sensitivity_range;

	sensitivity_range.start = MOUSE_MIN_SENSITIVITY;
	sensitivity_range.end = MOUSE_MAX_SENSITIVITY;
	marker_range.start
		= (double)cub3d->pause_menu.sensitivity_slider.marker_min_pos;
	marker_range.end
		= (double)cub3d->pause_menu.sensitivity_slider.marker_max_pos;
	return (lerp(sensitivity_range, marker_range,
			(double)cub3d->pause_menu.sensitivity_slider.marker->instances[0].x
			+ SLIDER_MARKER_WIDTH / 2));
}

void	disable_pause_menu(mlx_t *mlx, pause_menu_t *menu)
{
	mlx_delete_image(mlx, menu->bg);
	mlx_delete_image(mlx, menu->menu);
	mlx_delete_image(mlx, menu->title.img);
	mlx_delete_image(mlx, menu->text_fps);
	mlx_delete_image(mlx, menu->text_fisheye);
	mlx_delete_image(mlx, menu->text_mouse);
	mlx_delete_image(mlx, menu->text_mouse_sensitivity);
	mlx_delete_image(mlx, menu->box_fps[0].text);
	mlx_delete_image(mlx, menu->box_fps[1].text);
	mlx_delete_image(mlx, menu->box_fps[2].text);
	mlx_delete_image(mlx, menu->box_fps[3].text);
	mlx_delete_image(mlx, menu->box_fisheye[0].text);
	mlx_delete_image(mlx, menu->box_fisheye[1].text);
	mlx_delete_image(mlx, menu->box_mouse[0].text);
	mlx_delete_image(mlx, menu->box_mouse[1].text);
	mlx_delete_image(mlx, menu->sensitivity_slider.marker);
}

void	draw_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	draw_background(menu->bg, set_transparency(PAUSE_MENU_BACKGROUND_COLOR,
			PAUSE_MENU_TRANSPARENCY));
	draw_background(menu->menu, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->menu);
	draw_slider(menu->menu, &menu->sensitivity_slider);
	add_category_text(cub3d, menu);
	add_checkbox_text(cub3d, menu);
}

int	enable_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	if (!pause_menu_helper(cub3d, menu))
		return (0);
	if (mlx_image_to_window(cub3d->mlx, menu->bg, 0, 0) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(cub3d->mlx, menu->menu, menu->menu_pos.x,
			menu->menu_pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(cub3d->mlx, menu->title.img, menu->title.pos.x,
			menu->title.pos.y) < 0)
		return (err("Failed to put image to window"));
	if (mlx_image_to_window(cub3d->mlx, menu->sensitivity_slider.marker,
			get_marker_pos(cub3d), menu->sensitivity_slider.marker_pos.y) < 0)
		return (err("Failed to put image to window"));
	draw_menu(cub3d, menu);
	return (SUCCESS);
}
