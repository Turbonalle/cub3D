/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:47:18 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:51:26 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	mouse_leaderboard(t_cub3d *cub3d, t_leaderboard *board)
{
	if (hover_image(cub3d, board->back.img))
	{
		disable_leaderboard(cub3d, board);
		enable_level_menu(&cub3d->level_menu);
		cub3d->state = STATE_LEVEL;
	}
}

//------------------------------------------------------------------------------

void	mouse_entername_menu(t_cub3d *cub3d, t_name_menu *menu)
{
	if (hover_image(cub3d, menu->back.img))
	{
		disable_name_menu(cub3d->mlx, menu);
		enable_level_menu(&cub3d->level_menu);
		cub3d->state = STATE_LEVEL;
		cub3d->name_menu.changed = FALSE;
		cub3d->speedrun = FALSE;
	}
}
