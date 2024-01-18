/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:08:16 by vvagapov          #+#    #+#             */
/*   Updated: 2024/01/18 11:12:48 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	check_movement_keys(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_W)
		return (cub3d->keys.w = TRUE, 1);
	else if (keydata.key == MLX_KEY_A)
		return (cub3d->keys.a = TRUE, 1);
	else if (keydata.key == MLX_KEY_S)
		return (cub3d->keys.s = TRUE, 1);
	else if (keydata.key == MLX_KEY_D)
		return (cub3d->keys.d = TRUE, 1);
	else if (keydata.key == MLX_KEY_LEFT)
		return (cub3d->keys.left = TRUE, 1);
	else if (keydata.key == MLX_KEY_RIGHT)
		return (cub3d->keys.right = TRUE, 1);
	else if (keydata.key == MLX_KEY_UP)
		return (cub3d->keys.up = TRUE, 1);
	else if (keydata.key == MLX_KEY_DOWN)
		return (cub3d->keys.down = TRUE, 1);
	return (0);
}

static int	check_util_keys(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_P)
	{
		pause_timer(cub3d);
		enable_pause_menu(cub3d, &cub3d->pause_menu);
		cub3d->state = STATE_PAUSE;
		handle_cursor(cub3d);
		return (1);
	}
	else if (keydata.key == MLX_KEY_T)
		return (1);
	else if (keydata.key == MLX_KEY_SPACE)
	{
		if (cub3d->player.mushroom_count > 0)
			cause_distraction(cub3d);
		return (1);
	}
	return (0);
}

static int	check_escape(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		if (cub3d->player.thrown)
			cub3d->level->distractions[cub3d->level->num_distractions]
				.img_distraction->instances[0].enabled = FALSE;
		mlx_delete_image(cub3d->mlx, cub3d->timer.img_time);
		free_level(cub3d);
		if (cub3d->speedrun)
		{
			enable_level_menu(&cub3d->level_menu);
			cub3d->speedrun = FALSE;
			cub3d->state = STATE_LEVEL;
		}
		else
		{
			enable_start_menu(&cub3d->start_menu);
			cub3d->speedrun = FALSE;
			cub3d->state = STATE_START;
		}
		handle_cursor(cub3d);
		return (1);
	}
	return (0);
}

void	handle_game_input(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (check_movement_keys(keydata, cub3d))
		return ;
	else if (check_util_keys(keydata, cub3d))
		return ;
	else if (check_escape(keydata, cub3d))
		return ;
	else if (keydata.key == MLX_KEY_G)
	{
		if (cub3d->player.is_dirty_cheater < 2)
			cub3d->player.is_dirty_cheater++;
		else if (cub3d->player.is_dirty_cheater >= 2)
			cub3d->player.is_dirty_cheater--;
	}
	else if (keydata.key == MLX_KEY_PERIOD)
		cub3d->draw_floor = !cub3d->draw_floor;
}
