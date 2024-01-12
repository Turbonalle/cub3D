/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:23:45 by slampine          #+#    #+#             */
/*   Updated: 2024/01/12 12:00:21 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_input_first_third(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_Q)
		return (cub3d->keys.q = TRUE, 1);
	else if (keydata.key == MLX_KEY_W)
		return (cub3d->keys.w = TRUE, 1);
	else if (keydata.key == MLX_KEY_E)
		return (cub3d->keys.e = TRUE, 1);
	else if (keydata.key == MLX_KEY_R)
		return (cub3d->keys.r = TRUE, 1);
	else if (keydata.key == MLX_KEY_T)
		return (cub3d->keys.t = TRUE, 1);
	else if (keydata.key == MLX_KEY_Y)
		return (cub3d->keys.y = TRUE, 1);
	else if (keydata.key == MLX_KEY_U)
		return (cub3d->keys.u = TRUE, 1);
	else if (keydata.key == MLX_KEY_I)
		return (cub3d->keys.i = TRUE, 1);
	else if (keydata.key == MLX_KEY_O)
		return (cub3d->keys.o = TRUE, 1);
	else if (keydata.key == MLX_KEY_P)
		return (cub3d->keys.p = TRUE, 1);
	else if (keydata.key == MLX_KEY_A)
		return (cub3d->keys.a = TRUE, 1);
	return (0);
}

int	check_input_second_third(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_S)
		return (cub3d->keys.s = TRUE, 1);
	else if (keydata.key == MLX_KEY_D)
		return (cub3d->keys.d = TRUE, 1);
	else if (keydata.key == MLX_KEY_F)
		return (cub3d->keys.f = TRUE, 1);
	else if (keydata.key == MLX_KEY_G)
		return (cub3d->keys.g = TRUE, 1);
	else if (keydata.key == MLX_KEY_H)
		return (cub3d->keys.h = TRUE, 1);
	else if (keydata.key == MLX_KEY_J)
		return (cub3d->keys.j = TRUE, 1);
	else if (keydata.key == MLX_KEY_K)
		return (cub3d->keys.k = TRUE, 1);
	else if (keydata.key == MLX_KEY_L)
		return (cub3d->keys.l = TRUE, 1);
	else if (keydata.key == MLX_KEY_Z)
		return (cub3d->keys.z = TRUE, 1);
	else if (keydata.key == MLX_KEY_X)
		return (cub3d->keys.x = TRUE, 1);
	else if (keydata.key == MLX_KEY_C)
		return (cub3d->keys.c = TRUE, 1);
	return (0);
}

void	handle_name_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	cub3d->name_menu.changed = TRUE;
	if (check_input_first_third(keydata, cub3d))
		return ;
	else if (check_input_second_third(keydata, cub3d))
		return ;
	else if (keydata.key == MLX_KEY_V)
		cub3d->keys.v = TRUE;
	else if (keydata.key == MLX_KEY_B)
		cub3d->keys.b = TRUE;
	else if (keydata.key == MLX_KEY_N)
		cub3d->keys.n = TRUE;
	else if (keydata.key == MLX_KEY_M)
		cub3d->keys.m = TRUE;
	else if (keydata.key == MLX_KEY_SPACE)
		cub3d->keys.space = TRUE;
	else if (keydata.key == MLX_KEY_BACKSPACE)
		cub3d->keys.backspace = TRUE;
	else if (keydata.key == MLX_KEY_ENTER)
		cub3d->keys.enter = TRUE;
	else if (keydata.key == MLX_KEY_ESCAPE)
		cub3d->keys.escape = TRUE;
}

void	handle_pause_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_P || keydata.key == MLX_KEY_ESCAPE)
	{
		disable_pause_menu(cub3d->mlx, &cub3d->pause_menu);
		cub3d->state = STATE_GAME;
		handle_cursor(cub3d);
		continue_timer(cub3d);
	}
}

void	handle_start_input(mlx_key_data_t keydata, cub3d_t *cub3d)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cub3d->mlx);
}
