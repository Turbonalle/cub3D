#include "cub3d.h"

void print_settings(cub3d_t *cub3d)
{
	printf(TERMINAL_CYAN"[SETTINGS]\n"TERMINAL_RESET);
	printf("FPS: "TERMINAL_GREEN"%d"TERMINAL_RESET"\n", cub3d->settings.fps);
	printf("Fisheye: "TERMINAL_GREEN"%d"TERMINAL_RESET"\n", cub3d->settings.fisheye);
	printf("Mouse: "TERMINAL_GREEN"%d"TERMINAL_RESET"\n", cub3d->settings.mouse);
}

void update_fps_boxes(cub3d_t *cub3d, pause_menu_t *menu, int n)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (i == n)
			menu->box_fps[i].state = TRUE;
		else
			menu->box_fps[i].state = FALSE;
	}
	if (n == 0)
		cub3d->settings.fps = 15;
	else if (n == 1)
		cub3d->settings.fps = 30;
	else if (n == 2)
		cub3d->settings.fps = 60;
	else
		cub3d->settings.fps = 120;
}

void update_fisheye_boxes(cub3d_t *cub3d, pause_menu_t *menu, int n)
{
	int i;

	i = -1;
	while (++i < 2)
	{
		if (i == n)
			menu->box_fisheye[i].state = TRUE;
		else
			menu->box_fisheye[i].state = FALSE;
	}
	if (n == 0)
		cub3d->settings.fisheye = ON;
	else
		cub3d->settings.fisheye = OFF;
}

void update_mouse_boxes(cub3d_t *cub3d, pause_menu_t *menu, int n)
{
	int i;

	i = -1;
	while (++i < 2)
	{
		if (i == n)
			menu->box_mouse[i].state = TRUE;
		else
			menu->box_mouse[i].state = FALSE;
	}
	if (n == 0)
		cub3d->settings.mouse = ON;
	else
		cub3d->settings.mouse = OFF;
}

void update_pause_settings(cub3d_t *cub3d, pause_menu_t *menu)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (hover_box(cub3d, &menu->box_fps[i]))
		{
			if (menu->box_fps[i].state == FALSE)
				update_fps_boxes(cub3d, menu, i);
			break ;
		}
	}
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_fisheye[i]))
		{
			if (menu->box_fisheye[i].state == FALSE)
				update_fisheye_boxes(cub3d, menu, i);
			break ;
		}
	}
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_mouse[i]))
		{
			if (menu->box_mouse[i].state == FALSE)
				update_mouse_boxes(cub3d, menu, i);
			break ;
		}
	}
	print_settings(cub3d);
}

void update_pause_menu(cub3d_t *cub3d, pause_menu_t *menu)
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
