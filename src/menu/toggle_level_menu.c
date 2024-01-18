/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_level_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:37:33 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:51:36 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	disable_level_menu(t_level_menu *menu)
{
	int	i;

	menu->img->instances[0].enabled = FALSE;
	menu->title.img->instances[0].enabled = FALSE;
	menu->back.img->instances[0].enabled = FALSE;
	menu->leaderboard.img->instances[0].enabled = FALSE;
	menu->back_hover.img->instances[0].enabled = FALSE;
	menu->leaderboard_hover.img->instances[0].enabled = FALSE;
	i = -1;
	while (++i < LEVELS)
	{
		menu->minilevels[i].img->instances[0].enabled = FALSE;
		menu->minilevels[i].number.img->instances[0].enabled = FALSE;
		menu->minilevels[i].border->instances[0].enabled = FALSE;
	}
}

void	enable_level_menu(t_level_menu *menu)
{
	int	i;

	menu->img->instances[0].enabled = TRUE;
	menu->title.img->instances[0].enabled = TRUE;
	menu->back.img->instances[0].enabled = TRUE;
	menu->leaderboard.img->instances[0].enabled = TRUE;
	menu->back_hover.img->instances[0].enabled = FALSE;
	menu->leaderboard_hover.img->instances[0].enabled = FALSE;
	i = -1;
	while (++i < LEVELS)
	{
		menu->minilevels[i].img->instances[0].enabled = TRUE;
		menu->minilevels[i].number.img->instances[0].enabled = TRUE;
		menu->minilevels[i].border->instances[0].enabled = FALSE;
	}
}
