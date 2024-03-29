/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pause_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:46:23 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:52:09 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_settings(t_cub3d *cub3d, t_pause_menu *menu)
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
}

void	update_fps_boxes(t_pause_menu *menu, int n)
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

void	update_fisheye_boxes(t_pause_menu *menu, int n)
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

void	update_mouse_boxes(t_pause_menu *menu, int n)
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

void	update_pause_settings(t_cub3d *cub3d, t_pause_menu *menu)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (hover_box(cub3d, &menu->box_fps[i]))
		{
			if (menu->box_fps[i].state == FALSE)
				update_fps_boxes(menu, i);
		}
		if (i < 2)
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
	}
	update_settings(cub3d, menu);
}
