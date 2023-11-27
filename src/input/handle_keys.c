/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:08:45 by slampine          #+#    #+#             */
/*   Updated: 2023/11/27 13:06:45 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	handle_keypresses(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_W)
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
	else if (keydata.key == MLX_KEY_SPACE)
		cub3d->keys.fisheye = TRUE;
	else if (keydata.key == MLX_KEY_P)
	{
		if (cub3d->state == STATE_PAUSE)
		{
			delete_pause_menu(cub3d);
			cub3d->state = STATE_GAME;
		}
		else if (cub3d->state == STATE_GAME)
		{
			draw_pause_menu(cub3d, &cub3d->pause_menu);
			cub3d->state = STATE_PAUSE;
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
	else if (keydata.key == MLX_KEY_SPACE)
	{
		cub3d->keys.fisheye = FALSE;
		cub3d->prev = 0;
	}
}

void	get_input(mlx_key_data_t keydata, void *param)
{
	cub3d_t	*cub3d;

	cub3d = param;
	handle_escape_key(&keydata, cub3d->mlx);
	if (keydata.action == MLX_PRESS)
		handle_keypresses(keydata, cub3d);
	else if (keydata.action == MLX_RELEASE)
		handle_keyreleases(keydata, cub3d);
}