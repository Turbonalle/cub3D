/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:17:12 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/19 16:10:45 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	draw_game_background(t_cub3d *cub3d)
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
				mlx_put_pixel(cub3d->img, column, row,
					cub3d->level->ceiling_color);
			else
				mlx_put_pixel(cub3d->img, column, row,
					cub3d->level->floor_color);
		}
	}
}

void	handle_state_game(t_cub3d *cub3d)
{
	handle_fps(cub3d);
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse.x, &cub3d->mouse.y);
	if (cub3d->keys.mouse_left && cub3d->on_minimap)
	{
		move_minimap_x(cub3d);
		move_minimap_y(cub3d);
	}
	player_movement(cub3d);
	if (cub3d->state == STATE_GAME)
	{
		draw_game_background(cub3d);
		raycasting(cub3d);
		draw_world(cub3d);
		minimap(cub3d);
		enemy_vision(cub3d);
		draw_enemies(cub3d);
		draw_timer(cub3d);
		draw_game_entities(cub3d);
		handle_halo(&cub3d->halo);
		if (cub3d->level->distraction_amount)
			cub3d->level->distraction_amount -= FOOD_ROTTING_SPEED;
	}
	if (cub3d->player.health <= 0)
		game_over(cub3d);
}

void	update(void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (cub3d->state == STATE_START)
		update_start_menu(cub3d, &cub3d->start_menu);
	else if (cub3d->state == STATE_LEVEL)
		update_level_menu(cub3d, &cub3d->level_menu);
	else if (cub3d->state == STATE_LEADERBOARD)
		update_leaderboard(cub3d, &cub3d->leaderboard);
	else if (cub3d->state == STATE_PAUSE)
	{
		update_pause_menu(cub3d, &cub3d->pause_menu);
		if (cub3d->settings.fisheye == OFF)
			cub3d->fov = FOV;
	}
	else if (cub3d->state == STATE_GAME)
		handle_state_game(cub3d);
	else if (cub3d->state == STATE_ENTERNAME)
		update_name_menu(cub3d, &cub3d->name_menu);
	else if (cub3d->state == STATE_GAMEOVER)
		update_gameover_menu(cub3d, &cub3d->gameover_menu);
}

void	start_game(t_cub3d *cub3d)
{
	enable_start_menu(&cub3d->start_menu);
	mlx_close_hook(cub3d->mlx, &handle_close_window, cub3d->mlx);
	mlx_key_hook(cub3d->mlx, &get_input, cub3d);
	mlx_scroll_hook(cub3d->mlx, &hook_mouse_scroll, cub3d);
	mlx_mouse_hook(cub3d->mlx, &hook_mouse_buttons, cub3d);
	mlx_loop_hook(cub3d->mlx, &update, cub3d);
	mlx_loop(cub3d->mlx);
}
