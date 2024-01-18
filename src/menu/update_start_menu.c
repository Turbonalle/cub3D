/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_start_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:43:34 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:51:59 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static void	check_hover_exit(t_cub3d *cub3d, t_start_menu *menu)
{
	if (hover_image(cub3d, menu->exit.img))
	{
		menu->exit_hover.img->instances[0].enabled = TRUE;
		menu->exit.img->instances[0].enabled = FALSE;
		menu->arrow_exit.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->exit_hover.img->instances[0].enabled = FALSE;
		menu->exit.img->instances[0].enabled = TRUE;
		menu->arrow_exit.img->instances[0].enabled = FALSE;
	}
}

static void	check_hover_start(t_cub3d *cub3d, t_start_menu *menu)
{
	if (hover_image(cub3d, menu->start.img))
	{
		menu->start_hover.img->instances[0].enabled = TRUE;
		menu->start.img->instances[0].enabled = FALSE;
		menu->arrow_start.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->start_hover.img->instances[0].enabled = FALSE;
		menu->start.img->instances[0].enabled = TRUE;
		menu->arrow_start.img->instances[0].enabled = FALSE;
	}
}

static void	check_hover_level(t_cub3d *cub3d, t_start_menu *menu)
{
	if (hover_image(cub3d, menu->level.img))
	{
		menu->level_hover.img->instances[0].enabled = TRUE;
		menu->level.img->instances[0].enabled = FALSE;
		menu->arrow_level.img->instances[0].enabled = TRUE;
	}
	else
	{
		menu->level_hover.img->instances[0].enabled = FALSE;
		menu->level.img->instances[0].enabled = TRUE;
		menu->arrow_level.img->instances[0].enabled = FALSE;
	}
}

void	update_start_menu(t_cub3d *cub3d, t_start_menu *menu)
{
	check_hover_exit(cub3d, menu);
	check_hover_start(cub3d, menu);
	check_hover_level(cub3d, menu);
}
