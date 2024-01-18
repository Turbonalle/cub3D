/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_level_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:19:36 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:51:36 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	check_hover_back(t_cub3d *cub3d, t_level_menu *menu)
{
	if (hover_image(cub3d, menu->back.img))
	{
		menu->back_hover.img->instances[0].enabled = TRUE;
		menu->back.img->instances[0].enabled = FALSE;
	}
	else
	{
		menu->back_hover.img->instances[0].enabled = FALSE;
		menu->back.img->instances[0].enabled = TRUE;
	}
}

void	update_level_menu(t_cub3d *cub3d, t_level_menu *menu)
{
	int	i;

	check_hover_back(cub3d, menu);
	if (hover_image(cub3d, menu->leaderboard.img))
	{
		menu->leaderboard_hover.img->instances[0].enabled = TRUE;
		menu->leaderboard.img->instances[0].enabled = FALSE;
	}
	else
	{
		menu->leaderboard_hover.img->instances[0].enabled = FALSE;
		menu->leaderboard.img->instances[0].enabled = TRUE;
	}
	i = -1;
	while (++i < LEVELS)
	{
		if (hover_image(cub3d, menu->minilevels[i].img))
		{
			menu->minilevels[i].border->instances[0].enabled = TRUE;
		}
		else
		{
			menu->minilevels[i].border->instances[0].enabled = FALSE;
		}
	}
}
