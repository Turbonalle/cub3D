#include "cub3d.h"

void update_fps_boxes(cub3d_t *cub3d, pause_menu_t *menu, int n)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (i != n)
			menu->box_fps[i].value = FALSE;
	}
	int fps[4] = {30, 60, 90, 120};
	cub3d->settings.fps = fps[n];
}

void update_fisheye_boxes(cub3d_t *cub3d, pause_menu_t *menu, int n)
{
	int i;

	i = -1;
	while (++i < 2)
	{
		if (i != n)
			menu->box_fisheye[i].value = FALSE;
	}
	cub3d->settings.fisheye = n;
}

void update_mouse_boxes(cub3d_t *cub3d, pause_menu_t *menu, int n)
{
	int i;

	i = -1;
	while (++i < 2)
	{
		if (i != n)
			menu->box_mouse[i].value = FALSE;
	}
	cub3d->settings.mouse = n;
}

void update_pause_settings(cub3d_t *cub3d, pause_menu_t *menu)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (hover_box(cub3d, &menu->box_fps[i]))
		{
			if (menu->box_fps[i].value == TRUE)
				menu->box_fps[i].value = FALSE;
			else
				menu->box_fps[i].value = TRUE;
			break ;
		}
	}
	if (i < 4)
		update_fps_boxes(cub3d, menu, i);
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_fisheye[i]))
		{
			if (menu->box_fisheye[i].value == TRUE)
				menu->box_fisheye[i].value = FALSE;
			else
				menu->box_fisheye[i].value = TRUE;
			break ;
		}
	}
	if (i < 2)
		update_fisheye_boxes(cub3d, menu, i);
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_mouse[i]))
		{
			if (menu->box_mouse[i].value == TRUE)
				menu->box_mouse[i].value = FALSE;
			else
				menu->box_mouse[i].value = TRUE;
			break ;
		}
	}
	if (i < 2)
		update_mouse_boxes(cub3d, menu, i);

}

void pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
{
	// Here we update the settings if the user has changed them
	int i;

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
	
}