/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:10:57 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:50 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	left_mouse_button_press(t_cub3d *cub3d)
{
	if (cub3d->state == STATE_GAME && cub3d->settings.mouse == FALSE)
		mouse_game(cub3d);
	else if (cub3d->state == STATE_PAUSE)
		mouse_pause_menu(cub3d, &cub3d->pause_menu);
	else if (cub3d->state == STATE_START)
		mouse_start_menu(cub3d);
	else if (cub3d->state == STATE_LEVEL)
		mouse_level_menu(cub3d);
	else if (cub3d->state == STATE_LEADERBOARD)
		mouse_leaderboard(cub3d, &cub3d->leaderboard);
	else if (cub3d->state == STATE_GAMEOVER)
		mouse_gameover_menu(cub3d, &cub3d->gameover_menu);
	else if (cub3d->state == STATE_ENTERNAME)
		mouse_entername_menu(cub3d, &cub3d->name_menu);
	else if (cub3d->state == STATE_INTRO)
		mouse_intro(cub3d);
}

void	hook_mouse_buttons(enum mouse_key key, enum action action,
	enum modifier_key modifier, void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	(void)modifier;
	if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		cub3d->keys.mouse_left = TRUE;
		left_mouse_button_press(cub3d);
	}
	else if (key == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
	{
		cub3d->on_minimap = FALSE;
		cub3d->keys.mouse_left = FALSE;
	}
	else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		cub3d->keys.mouse_right = TRUE;
	else if (key == MLX_MOUSE_BUTTON_RIGHT && action == MLX_RELEASE)
		cub3d->keys.mouse_right = FALSE;
}

void	hook_mouse_scroll(double xdelta, double ydelta, void *param)
{
	t_cub3d	*cub3d;

	(void)xdelta;
	cub3d = param;
	if (cub3d->state == STATE_GAME && cub3d->settings.mouse == FALSE)
	{
		if (ydelta > 0 && hover_minimap(cub3d))
		{
			if (!zoom_in_minimap(cub3d))
				mlx_close_window(cub3d->mlx);
		}
		else if (ydelta < 0 && hover_minimap(cub3d))
		{
			if (!zoom_out_minimap(cub3d))
				mlx_close_window(cub3d->mlx);
		}
	}
}
