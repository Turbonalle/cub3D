/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toggle_gameover_menu.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:38:31 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:50:01 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	disable_gameover_menu(mlx_t *mlx, t_gameover_menu *menu)
{
	mlx_delete_image(mlx, menu->text_time);
	menu->img->instances[0].enabled = FALSE;
	menu->title_win.img->instances[0].enabled = FALSE;
	menu->title_gameover.img->instances[0].enabled = FALSE;
	menu->timer.img->instances[0].enabled = FALSE;
	menu->back.img->instances[0].enabled = FALSE;
	menu->back_hover.img->instances[0].enabled = FALSE;
	menu->restart.img->instances[0].enabled = FALSE;
	menu->restart_hover.img->instances[0].enabled = FALSE;
	menu->arrow_back.img->instances[0].enabled = FALSE;
	menu->arrow_restart.img->instances[0].enabled = FALSE;
}

void	enable_gameover_menu(t_cub3d *cub3d, t_gameover_menu *menu, int win)
{
	create_time_string(menu->time_str, cub3d->time_finished);
	menu->text_time = mlx_put_string(cub3d->mlx, menu->time_str,
			menu->timer.pos.x + menu->timer.img->width * 0.5,
			menu->timer.pos.y + menu->timer.img->height + 10);
	center_horizontally(menu->text_time);
	menu->img->instances[0].enabled = TRUE;
	if (win == WIN)
		menu->title_win.img->instances[0].enabled = TRUE;
	else
		menu->title_gameover.img->instances[0].enabled = TRUE;
	menu->timer.img->instances[0].enabled = TRUE;
	menu->back.img->instances[0].enabled = TRUE;
	menu->restart.img->instances[0].enabled = TRUE;
}
