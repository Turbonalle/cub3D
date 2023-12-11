/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:37 by slampine          #+#    #+#             */
/*   Updated: 2023/12/08 13:53:30 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_background(cub3d_t *cub3d)
{
	unsigned int	row;
	unsigned int	column;

	row = -1;
	while (++row < cub3d->img->height)
	{
		column = -1;
		while (++column < cub3d->img->width)
		{
			if (row < cub3d->img->height / 2)
				mlx_put_pixel(cub3d->img, column, row, cub3d->level->ceiling_color);
			else
				mlx_put_pixel(cub3d->img, column, row, cub3d->level->floor_color);
		}
	}
}

//------------------------------------------------------------------------------

void	update_img_size(cub3d_t *cub3d)
{
	if ((int)cub3d->img->width != cub3d->mlx->width || (int)cub3d->img->height != cub3d->mlx->height)
	{
		mlx_delete_image(cub3d->mlx, cub3d->img);
		cub3d->img = mlx_new_image(cub3d->mlx, cub3d->mlx->width, cub3d->mlx->height);
		update_minimap(cub3d);
		mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0);
		if (!init_rays(cub3d))
		{
			err("Failed to malloc rays");
			mlx_close_window(cub3d->mlx);
		}
	}
}
//------------------------------------------------------------------------------

void	update(void *param)
{
	cub3d_t	*cub3d;

	cub3d = param;

	// TODO: add crash handling if (cub3d->state == STATE_CRASH)
	if (cub3d->state == STATE_START)
	{
		update_start_menu(cub3d, &cub3d->start_menu);
	}
	else if (cub3d->state == STATE_LEVEL)
	{
		update_level_menu(cub3d, &cub3d->level_menu);
	}
	else if (cub3d->state == STATE_LEADERBOARD)
	{
		update_leaderboard(cub3d, &cub3d->leaderboard);
	}
	else if (cub3d->state == STATE_SETTINGS)
	{
		// update_settings_menu(cub3d, &cub3d->settings_menu);
	}
	else if (cub3d->state == STATE_PAUSE)
	{
		update_pause_menu(cub3d, &cub3d->pause_menu);
		if (cub3d->settings.fisheye == OFF)
			cub3d->fov = FOV;
	}
	else if (cub3d->state == STATE_GAME)
	{
		handle_fps(cub3d);
		update_img_size(cub3d);
		mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse.x, &cub3d->mouse.y);
		if (cub3d->keys.mouse_left && cub3d->on_minimap)
			move_minimap(cub3d);
		player_movement(cub3d);
		draw_background(cub3d);
		raycasting(cub3d);
		draw_world(cub3d);
		minimap(cub3d);
		enemy_vision(cub3d);
		draw_timer(cub3d);
		draw_animated_keys(cub3d);
		// print_timer(cub3d);	// REMOVE
	}
	else if (cub3d->state == STATE_GAMEOVER)
	{
		// update_end_menu(cub3d, &cub3d->gameover_menu);
		cub3d->state = STATE_START;
	}
}

void	start_game(cub3d_t *cub3d)
{
	draw_start_menu(cub3d, &cub3d->start_menu);
	mlx_close_hook(cub3d->mlx, &handle_close_window, cub3d->mlx);
	mlx_key_hook(cub3d->mlx, &get_input, cub3d);
	mlx_scroll_hook(cub3d->mlx, &hook_mouse_scroll, cub3d);
	mlx_mouse_hook(cub3d->mlx, &hook_mouse_buttons, cub3d);
	mlx_loop_hook(cub3d->mlx, &update, cub3d);
	mlx_loop(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
}
