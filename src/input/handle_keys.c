/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbagger <jbagger@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:45 by slampine          #+#    #+#             */
/*   Updated: 2023/12/06 14:57:56 by jbagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	keypress_name_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	cub3d->name_menu.changed = TRUE;
	if (keydata.key == MLX_KEY_Q)
		cub3d->name_menu.letter = 'q';
	else if (keydata.key == MLX_KEY_W)
		cub3d->name_menu.letter = 'w';
	else if (keydata.key == MLX_KEY_E)
		cub3d->name_menu.letter = 'e';
	else if (keydata.key == MLX_KEY_R)
		cub3d->name_menu.letter = 'r';
	else if (keydata.key == MLX_KEY_T)
		cub3d->name_menu.letter = 't';
	else if (keydata.key == MLX_KEY_Y)
		cub3d->name_menu.letter = 'y';
	else if (keydata.key == MLX_KEY_U)
		cub3d->name_menu.letter = 'u';
	else if (keydata.key == MLX_KEY_I)
		cub3d->name_menu.letter = 'i';
	else if (keydata.key == MLX_KEY_O)
		cub3d->name_menu.letter = 'o';
	else if (keydata.key == MLX_KEY_P)
		cub3d->name_menu.letter = 'p';
	else if (keydata.key == MLX_KEY_A)
		cub3d->name_menu.letter = 'a';
	else if (keydata.key == MLX_KEY_S)
		cub3d->name_menu.letter = 's';
	else if (keydata.key == MLX_KEY_D)
		cub3d->name_menu.letter = 'd';
	else if (keydata.key == MLX_KEY_F)
		cub3d->name_menu.letter = 'f';
	else if (keydata.key == MLX_KEY_G)
		cub3d->name_menu.letter = 'g';
	else if (keydata.key == MLX_KEY_H)
		cub3d->name_menu.letter = 'h';
	else if (keydata.key == MLX_KEY_J)
		cub3d->name_menu.letter = 'j';
	else if (keydata.key == MLX_KEY_K)
		cub3d->name_menu.letter = 'k';
	else if (keydata.key == MLX_KEY_L)
		cub3d->name_menu.letter = 'l';
	else if (keydata.key == MLX_KEY_Z)
		cub3d->name_menu.letter = 'z';
	else if (keydata.key == MLX_KEY_X)
		cub3d->name_menu.letter = 'x';
	else if (keydata.key == MLX_KEY_C)
		cub3d->name_menu.letter = 'c';
	else if (keydata.key == MLX_KEY_V)
		cub3d->name_menu.letter = 'v';
	else if (keydata.key == MLX_KEY_B)
		cub3d->name_menu.letter = 'b';
	else if (keydata.key == MLX_KEY_N)
		cub3d->name_menu.letter = 'n';
	else if (keydata.key == MLX_KEY_M)
		cub3d->name_menu.letter = 'm';
	else if (keydata.key == MLX_KEY_SPACE)
		cub3d->name_menu.letter = ' ';
	else if (keydata.key == MLX_KEY_LEFT_SHIFT || keydata.key == MLX_KEY_RIGHT_SHIFT)
		cub3d->keys.shift = TRUE;
	else if (keydata.key == MLX_KEY_BACKSPACE)
		cub3d->keys.backspace = TRUE;
	else if (keydata.key == MLX_KEY_ENTER)
		cub3d->keys.enter = TRUE;
	else if (keydata.key == MLX_KEY_ESCAPE)
		cub3d->keys.escape = TRUE;
}

void	handle_keypresses(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (cub3d->state == STATE_ENTERNAME)
		keypress_name_input(keydata, cub3d);
	else if (keydata.key == MLX_KEY_W)
		cub3d->keys.w = TRUE;
	else if (keydata.key == MLX_KEY_A)
		cub3d->keys.a = TRUE;
	else if (keydata.key == MLX_KEY_S)
		cub3d->keys.s = TRUE;
	else if (keydata.key == MLX_KEY_D)
		cub3d->keys.d = TRUE;
	else if (keydata.key == MLX_KEY_LEFT)
		cub3d->keys.left = TRUE;
	else if (keydata.key == MLX_KEY_RIGHT)
		cub3d->keys.right = TRUE;
	else if (keydata.key == MLX_KEY_UP)
		cub3d->keys.up = TRUE;
	else if (keydata.key == MLX_KEY_DOWN)
		cub3d->keys.down = TRUE;
	else if (keydata.key == MLX_KEY_P)
	{
		if (cub3d->state == STATE_PAUSE)
		{
			delete_pause_menu(cub3d);
			cub3d->state = STATE_GAME;
			continue_timer(cub3d);
		}
		else if (cub3d->state == STATE_GAME)
		{
			pause_timer(cub3d);
			draw_pause_menu(cub3d, &cub3d->pause_menu);
			cub3d->state = STATE_PAUSE;
		}
	}
	else if (keydata.key == MLX_KEY_T)
	{
		printf("Time passed: %f\n", mlx_get_time() - cub3d->start_timestamp);
	}
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		if (cub3d->state == STATE_GAME)
		{
			printf("Back to start menu\n");
			mlx_delete_image(cub3d->mlx, cub3d->minimap.img);
			draw_start_menu(cub3d, &cub3d->start_menu);
			// free enemies, keys, doors
			cub3d->state = STATE_START;
		}
		else if (cub3d->state == STATE_START)
		{
			mlx_close_window(cub3d->mlx);
		}
		else if (cub3d->state == STATE_LEVEL)
		{
			delete_level_menu(cub3d, &cub3d->level_menu);
			draw_start_menu(cub3d, &cub3d->start_menu);
			cub3d->state = STATE_START;
		}
		else if (cub3d->state == STATE_LEADERBOARD)
		{
			delete_leaderboard(cub3d, &cub3d->leaderboard);
			draw_level_menu(cub3d, &cub3d->level_menu);
			cub3d->state = STATE_LEVEL;
		}
		else if (cub3d->state == STATE_PAUSE)
		{
			delete_pause_menu(cub3d);
			cub3d->state = STATE_GAME;
			continue_timer(cub3d);
		}
		else if (cub3d->state == STATE_GAMEOVER)
		{
			// delete_gameover_menu(cub3d);
			draw_start_menu(cub3d, &cub3d->start_menu);
			cub3d->state = STATE_START;
		}
		else if (cub3d->state == STATE_SETTINGS)
		{
			// delete_settings_menu(cub3d, &cub3d->settings_menu);
			// draw_start_menu(cub3d, &cub3d->start_menu);
			cub3d->state = STATE_START;
		}
	}
}

void	handle_keyreleases(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_W)
		cub3d->keys.w = FALSE;
	else if (keydata.key == MLX_KEY_A)
		cub3d->keys.a = FALSE;
	else if (keydata.key == MLX_KEY_S)
		cub3d->keys.s = FALSE;
	else if (keydata.key == MLX_KEY_D)
		cub3d->keys.d = FALSE;
	else if (keydata.key == MLX_KEY_LEFT)
		cub3d->keys.left = FALSE;
	else if (keydata.key == MLX_KEY_RIGHT)
		cub3d->keys.right = FALSE;
	else if (keydata.key == MLX_KEY_UP)
		cub3d->keys.up = FALSE;
	else if (keydata.key == MLX_KEY_DOWN)
		cub3d->keys.down = FALSE;
	else if (keydata.key == MLX_KEY_LEFT_SHIFT || keydata.key == MLX_KEY_RIGHT_SHIFT)
		cub3d->keys.shift = FALSE;
	else if (keydata.key == MLX_KEY_BACKSPACE)
		cub3d->keys.backspace = FALSE;
	else if (keydata.key == MLX_KEY_ENTER)
		cub3d->keys.enter = FALSE;
	else if (keydata.key == MLX_KEY_ESCAPE)
		cub3d->keys.escape = FALSE;
}

void	get_input(mlx_key_data_t keydata, void *param)
{
	cub3d_t	*cub3d;

	cub3d = param;
	if (keydata.action == MLX_PRESS)
		handle_keypresses(keydata, cub3d);
	else if (keydata.action == MLX_RELEASE)
		handle_keyreleases(keydata, cub3d);
}