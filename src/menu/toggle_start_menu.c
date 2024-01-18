/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_start_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:22:18 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:51:59 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	disable_start_menu(t_start_menu *menu)
{
	menu->img->instances[0].enabled = FALSE;
	menu->title.img->instances[0].enabled = FALSE;
	menu->exit.img->instances[0].enabled = FALSE;
	menu->start.img->instances[0].enabled = FALSE;
	menu->level.img->instances[0].enabled = FALSE;
	menu->exit_hover.img->instances[0].enabled = FALSE;
	menu->start_hover.img->instances[0].enabled = FALSE;
	menu->level_hover.img->instances[0].enabled = FALSE;
	menu->arrow_exit.img->instances[0].enabled = FALSE;
	menu->arrow_start.img->instances[0].enabled = FALSE;
	menu->arrow_level.img->instances[0].enabled = FALSE;
}

void	enable_start_menu(t_start_menu *menu)
{
	menu->img->instances[0].enabled = TRUE;
	menu->title.img->instances[0].enabled = TRUE;
	menu->exit.img->instances[0].enabled = TRUE;
	menu->start.img->instances[0].enabled = TRUE;
	menu->level.img->instances[0].enabled = TRUE;
	menu->exit_hover.img->instances[0].enabled = FALSE;
	menu->start_hover.img->instances[0].enabled = FALSE;
	menu->level_hover.img->instances[0].enabled = FALSE;
	menu->arrow_exit.img->instances[0].enabled = FALSE;
	menu->arrow_start.img->instances[0].enabled = FALSE;
	menu->arrow_level.img->instances[0].enabled = FALSE;
}
