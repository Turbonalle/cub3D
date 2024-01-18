/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:17:04 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:50 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	handle_gameover_input(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		disable_gameover_menu(cub3d->mlx, &cub3d->gameover_menu);
		enable_start_menu(&cub3d->start_menu);
		cub3d->state = STATE_START;
	}
}

void	handle_intro_input(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_ENTER)
	{
		cub3d->level = &cub3d->levels[0];
		if (!load_level(cub3d, cub3d->level))
		{
			disable_intro(cub3d);
			enable_start_menu(&cub3d->start_menu);
			cub3d->state = STATE_START;
			return ;
		}
		disable_intro(cub3d);
		cub3d->settings.e_behaviour = cub3d->player.num_completed % 3;
		cub3d->settings.e_speed = cub3d->player.num_completed / 3;
		cub3d->intro_watched = TRUE;
		cub3d->state = STATE_GAME;
		handle_cursor(cub3d);
		start_timer(cub3d);
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		disable_intro(cub3d);
		enable_start_menu(&cub3d->start_menu);
		cub3d->state = STATE_START;
	}
}

void	handle_keypresses(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (cub3d->state == STATE_GAME)
		handle_game_input(keydata, cub3d);
	else if (cub3d->state == STATE_ENTERNAME)
		handle_name_input(keydata, cub3d);
	else if (cub3d->state == STATE_PAUSE)
		handle_pause_input(keydata, cub3d);
	else if (cub3d->state == STATE_START)
		handle_start_input(keydata, cub3d);
	else if (cub3d->state == STATE_LEVEL)
		handle_level_input(keydata, cub3d);
	else if (cub3d->state == STATE_LEADERBOARD)
		handle_leaderboard_input(keydata, cub3d);
	else if (cub3d->state == STATE_GAMEOVER)
		handle_gameover_input(keydata, cub3d);
	else if (cub3d->state == STATE_INTRO)
		handle_intro_input(keydata, cub3d);
}

void	get_input(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*cub3d;

	cub3d = param;
	if (keydata.action == MLX_PRESS)
		handle_keypresses(keydata, cub3d);
	else if (keydata.action == MLX_RELEASE)
		handle_keyreleases(keydata, cub3d);
}
