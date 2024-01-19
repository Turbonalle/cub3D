/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gameover_menu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:21:18 by slampine          #+#    #+#             */
/*   Updated: 2024/01/19 16:10:08 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	update_gameover_menu(t_cub3d *cub3d, t_gameover_menu *menu)
{
	if (hover_image(cub3d, menu->back.img))
	{
		menu->back.img->instances[0].enabled = FALSE;
		menu->back_hover.img->instances[0].enabled = TRUE;
		menu->arrow_back.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->back.img->instances[0].enabled = TRUE;
		menu->back_hover.img->instances[0].enabled = FALSE;
		menu->arrow_back.img->instances[0].enabled = FALSE;
	}
	if (hover_image(cub3d, menu->restart.img))
	{
		menu->restart.img->instances[0].enabled = FALSE;
		menu->restart_hover.img->instances[0].enabled = TRUE;
		menu->arrow_restart.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->restart.img->instances[0].enabled = TRUE;
		menu->restart_hover.img->instances[0].enabled = FALSE;
		menu->arrow_restart.img->instances[0].enabled = FALSE;
	}
}
