/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:47:18 by slampine          #+#    #+#             */
/*   Updated: 2024/01/12 11:47:30 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	mouse_leaderboard(cub3d_t *cub3d, leaderboard_t *board)
{
	if (hover_image(cub3d, board->back.img))
	{
		disable_leaderboard(cub3d, board);
		enable_level_menu(&cub3d->level_menu);
		cub3d->state = STATE_LEVEL;
	}
}

//------------------------------------------------------------------------------

void	mouse_entername_menu(cub3d_t *cub3d, name_menu_t *menu)
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
