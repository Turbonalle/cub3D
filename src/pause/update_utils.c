/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:46:26 by slampine          #+#    #+#             */
/*   Updated: 2024/01/11 15:05:41 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_slider_marker(cub3d_t *cub3d, slider_t *slider)
{
	int	mouse_moved;

	mouse_moved = cub3d->mouse.x - slider->marker_orig_pos;
	if (slider->marker_orig_pos + mouse_moved < slider->marker_min_pos)
	{
		slider->marker->instances[0].x = slider->marker_min_pos
			- SLIDER_MARKER_WIDTH / 2;
	}
	else if (slider->marker_orig_pos + mouse_moved > slider->marker_max_pos)
	{
		slider->marker->instances[0].x = slider->marker_max_pos
			- SLIDER_MARKER_WIDTH / 2;
	}
	else
	{
		slider->marker->instances[0].x = slider->marker_orig_pos
			+ mouse_moved - SLIDER_MARKER_WIDTH / 2;
	}
}

void	update_pause_mouse(cub3d_t *cub3d, pause_menu_t *menu)
{
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse.x, &cub3d->mouse.y);
	if (cub3d->keys.mouse_left && menu->sensitivity_slider.on_marker == TRUE)
	{
		move_slider_marker(cub3d, &menu->sensitivity_slider);
		update_settings(cub3d, menu);
	}
}

void	update_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (hover_box(cub3d, &menu->box_fps[i]))
			draw_hovered_checkbox(cub3d, &menu->box_fps[i]);
		else
			draw_checkbox(cub3d, &menu->box_fps[i]);
	}
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_fisheye[i]))
			draw_hovered_checkbox(cub3d, &menu->box_fisheye[i]);
		else
			draw_checkbox(cub3d, &menu->box_fisheye[i]);
		if (hover_box(cub3d, &menu->box_mouse[i]))
			draw_hovered_checkbox(cub3d, &menu->box_mouse[i]);
		else
			draw_checkbox(cub3d, &menu->box_mouse[i]);
	}
	update_pause_mouse(cub3d, menu);
}
