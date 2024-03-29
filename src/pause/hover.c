/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hover.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:02:02 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:53:15 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	hover_image(t_cub3d *cub3d, mlx_image_t *img)
{
	t_vector	mouse;

	mlx_get_mouse_pos(cub3d->mlx, &mouse.x, &mouse.y);
	if (mouse.x >= (int)img->instances[0].x
		&& mouse.x <= (int)(img->instances[0].x + img->width)
		&& mouse.y >= (int)img->instances[0].y
		&& mouse.y <= (int)(img->instances[0].y + img->height))
		return (TRUE);
	return (FALSE);
}

int	hover_button(t_cub3d *cub3d, t_button *button)
{
	int	mouse_x;
	int	mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	return (mouse_x >= button->pos.x
		&& mouse_x <= button->pos.x + button->width
		&& mouse_y >= button->pos.y
		&& mouse_y <= button->pos.y + button->height);
}

int	hover_rectangle(t_cub3d *cub3d, t_rectangle *rect)
{
	int	mouse_x;
	int	mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	return (mouse_x >= rect->pos.x
		&& mouse_x <= rect->pos.x + rect->width
		&& mouse_y >= rect->pos.y
		&& mouse_y <= rect->pos.y + rect->height);
}

int	hover_box(t_cub3d *cub3d, t_box *box)
{
	int	mouse_x;
	int	mouse_y;

	mlx_get_mouse_pos(cub3d->mlx, &mouse_x, &mouse_y);
	return (mouse_x - cub3d->pause_menu.menu_pos.x >= box->pos.x
		&& mouse_x - cub3d->pause_menu.menu_pos.x <= box->pos.x + box->size
		&& mouse_y - cub3d->pause_menu.menu_pos.y >= box->pos.y
		&& mouse_y - cub3d->pause_menu.menu_pos.y <= box->pos.y + box->size);
}

int	hover_any_box(t_cub3d *cub3d, t_pause_menu *menu)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (hover_box(cub3d, &menu->box_fps[i]))
			return (TRUE);
	}
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_fisheye[i]))
			return (TRUE);
	}
	i = -1;
	while (++i < 2)
	{
		if (hover_box(cub3d, &menu->box_mouse[i]))
			return (TRUE);
	}
	return (FALSE);
}
