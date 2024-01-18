/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_pause_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:49:00 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 11:15:34 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	get_marker_pos(t_cub3d *cub3d)
{
	t_range	marker_range;
	t_range	sensitivity_range;

	marker_range.start = cub3d->pause_menu.sensitivity_slider.marker_min_pos;
	marker_range.end = cub3d->pause_menu.sensitivity_slider.marker_max_pos;
	sensitivity_range.start = MOUSE_MIN_SENSITIVITY;
	sensitivity_range.end = MOUSE_MAX_SENSITIVITY;
	return (lerp(marker_range, sensitivity_range,
			cub3d->settings.mouse_sensitivity) - SLIDER_MARKER_WIDTH / 2);
}

double	get_sensitivity(t_cub3d *cub3d)
{
	t_range	marker_range;
	t_range	sensitivity_range;

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

void	disable_pause_menu(mlx_t *mlx, t_pause_menu *menu)
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

void	draw_menu(t_cub3d *cub3d, t_pause_menu *menu)
{
	draw_background(menu->bg, set_transparency(PAUSE_MENU_BACKGROUND_COLOR,
			PAUSE_MENU_TRANSPARENCY));
	draw_background(menu->menu, MENU_BACKGROUND_COLOR);
	draw_menu_border(menu->menu);
	draw_slider(menu->menu, &menu->sensitivity_slider);
	add_category_text(cub3d, menu);
	add_checkbox_text(cub3d, menu);
}

int	enable_pause_menu(t_cub3d *cub3d, t_pause_menu *menu)
{
	if (!pause_menu_helper(cub3d, menu))
		return (FAIL);
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
