/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyrelease_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:50:06 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	check_first_third(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_Q)
		return (cub3d->keys.q = FALSE, 1);
	else if (keydata.key == MLX_KEY_W)
		return (cub3d->keys.w = FALSE, 1);
	else if (keydata.key == MLX_KEY_E)
		return (cub3d->keys.e = FALSE, 1);
	else if (keydata.key == MLX_KEY_R)
		return (cub3d->keys.r = FALSE, 1);
	else if (keydata.key == MLX_KEY_T)
		return (cub3d->keys.t = FALSE, 1);
	else if (keydata.key == MLX_KEY_Y)
		return (cub3d->keys.y = FALSE, 1);
	else if (keydata.key == MLX_KEY_U)
		return (cub3d->keys.u = FALSE, 1);
	else if (keydata.key == MLX_KEY_I)
		return (cub3d->keys.i = FALSE, 1);
	else if (keydata.key == MLX_KEY_O)
		return (cub3d->keys.o = FALSE, 1);
	else if (keydata.key == MLX_KEY_P)
		return (cub3d->keys.p = FALSE, 1);
	else if (keydata.key == MLX_KEY_A)
		return (cub3d->keys.a = FALSE, 1);
	else if (keydata.key == MLX_KEY_S)
		return (cub3d->keys.s = FALSE, 1);
	return (0);
}

static int	check_second_third(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_D)
		return (cub3d->keys.d = FALSE, 1);
	else if (keydata.key == MLX_KEY_F)
		return (cub3d->keys.f = FALSE, 1);
	else if (keydata.key == MLX_KEY_G)
		return (cub3d->keys.g = FALSE, 1);
	else if (keydata.key == MLX_KEY_H)
		return (cub3d->keys.h = FALSE, 1);
	else if (keydata.key == MLX_KEY_J)
		return (cub3d->keys.j = FALSE, 1);
	else if (keydata.key == MLX_KEY_K)
		return (cub3d->keys.k = FALSE, 1);
	else if (keydata.key == MLX_KEY_L)
		return (cub3d->keys.l = FALSE, 1);
	else if (keydata.key == MLX_KEY_Z)
		return (cub3d->keys.z = FALSE, 1);
	else if (keydata.key == MLX_KEY_X)
		return (cub3d->keys.x = FALSE, 1);
	else if (keydata.key == MLX_KEY_C)
		return (cub3d->keys.c = FALSE, 1);
	else if (keydata.key == MLX_KEY_V)
		return (cub3d->keys.v = FALSE, 1);
	else if (keydata.key == MLX_KEY_B)
		return (cub3d->keys.b = FALSE, 1);
	return (0);
}

void	handle_keyreleases(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (check_first_third(keydata, cub3d))
		return ;
	else if (check_second_third(keydata, cub3d))
		return ;
	else if (keydata.key == MLX_KEY_N)
		cub3d->keys.n = FALSE;
	else if (keydata.key == MLX_KEY_M)
		cub3d->keys.m = FALSE;
	else if (keydata.key == MLX_KEY_LEFT)
		cub3d->keys.left = FALSE;
	else if (keydata.key == MLX_KEY_RIGHT)
		cub3d->keys.right = FALSE;
	else if (keydata.key == MLX_KEY_UP)
		cub3d->keys.up = FALSE;
	else if (keydata.key == MLX_KEY_DOWN)
		cub3d->keys.down = FALSE;
	else if (keydata.key == MLX_KEY_SPACE)
		cub3d->keys.space = FALSE;
	else if (keydata.key == MLX_KEY_BACKSPACE)
		cub3d->keys.backspace = FALSE;
	else if (keydata.key == MLX_KEY_ENTER)
		cub3d->keys.enter = FALSE;
	else if (keydata.key == MLX_KEY_ESCAPE)
		cub3d->keys.escape = FALSE;
}

void	handle_level_input(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		disable_level_menu(&cub3d->level_menu);
		enable_start_menu(&cub3d->start_menu);
		cub3d->state = STATE_START;
	}
}

void	handle_leaderboard_input(mlx_key_data_t keydata, t_cub3d *cub3d)
{
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		disable_leaderboard(cub3d, &cub3d->leaderboard);
		enable_level_menu(&cub3d->level_menu);
		cub3d->state = STATE_LEVEL;
	}
}
