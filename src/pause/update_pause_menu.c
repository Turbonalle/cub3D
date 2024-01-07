#include "cub3d.h"

void	update_settings(cub3d_t *cub3d, pause_menu_t *menu)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (menu->box_fps[i].state == TRUE)
		{
			cub3d->settings.fps = menu->box_fps[i].value;
			set_fps(&cub3d->frame_time, cub3d->settings.fps);
		}
	}
	i = -1;
	while (++i < 2)
	{
		if (menu->box_fisheye[i].state == TRUE)
			cub3d->settings.fisheye = menu->box_fisheye[i].value;
		if (menu->box_mouse[i].state == TRUE)
			cub3d->settings.mouse = menu->box_mouse[i].value;
	}
	cub3d->settings.mouse_sensitivity = get_sensitivity(cub3d);
	printf("mouse sensitivity: %f\n", cub3d->settings.mouse_sensitivity);
}

void	update_fps_boxes(pause_menu_t *menu, int n)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (i == n)
			menu->box_fps[i].state = TRUE;
		else
			menu->box_fps[i].state = FALSE;
	}
}

void	update_fisheye_boxes(pause_menu_t *menu, int n)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (i == n)
			menu->box_fisheye[i].state = TRUE;
		else
			menu->box_fisheye[i].state = FALSE;
	}
}

void	update_mouse_boxes(pause_menu_t *menu, int n)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (i == n)
			menu->box_mouse[i].state = TRUE;
		else
			menu->box_mouse[i].state = FALSE;
	}
}

void	update_pause_settings(cub3d_t *cub3d, pause_menu_t *menu)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (hover_box(cub3d, &menu->box_fps[i]))
		{
			if (menu->box_fps[i].state == FALSE)
				update_fps_boxes(menu, i);
			break ;
		}
	}
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_fisheye[i]))
		{
			if (menu->box_fisheye[i].state == FALSE)
				update_fisheye_boxes(menu, i);
		}
		if (hover_box(cub3d, &menu->box_mouse[i]))
		{
			if (menu->box_mouse[i].state == FALSE)
				update_mouse_boxes(menu, i);
		}
	}
	update_settings(cub3d, menu);
	// print_settings(cub3d);
}

void	move_slider_marker(cub3d_t *cub3d, slider_t *slider)
{
	int	mouse_moved;

	mouse_moved = cub3d->mouse.x - slider->marker_orig_pos;
	if (slider->marker_orig_pos + mouse_moved < slider->marker_min_pos)
		slider->marker->instances[0].x = slider->marker_min_pos - SLIDER_MARKER_WIDTH / 2;
	else if (slider->marker_orig_pos + mouse_moved > slider->marker_max_pos)
		slider->marker->instances[0].x = slider->marker_max_pos - SLIDER_MARKER_WIDTH / 2;
	else
		slider->marker->instances[0].x = slider->marker_orig_pos + mouse_moved - SLIDER_MARKER_WIDTH / 2;
}

void	update_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	// Here we update the settings if the user has changed them
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
	}
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_mouse[i]))
			draw_hovered_checkbox(cub3d, &menu->box_mouse[i]);
		else
			draw_checkbox(cub3d, &menu->box_mouse[i]);
	}
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse.x, &cub3d->mouse.y);
	if (cub3d->keys.mouse_left && menu->sensitivity_slider.on_marker == TRUE)
	{
		move_slider_marker(cub3d, &menu->sensitivity_slider);
		update_settings(cub3d, menu);
	}
}
