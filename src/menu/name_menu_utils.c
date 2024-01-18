/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_menu_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:12:52 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:50:12 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	get_letter(t_cub3d *cub3d, t_name_menu *menu)
{
	if (get_letter_first_third(cub3d, menu))
		return ;
	else if (get_letter_second_third(cub3d, menu))
		return ;
	else
		get_letter_last_third(cub3d, menu);
}

int	change_name(t_cub3d *cub3d, t_name_menu *menu)
{
	if (cub3d->keys.escape)
	{
		disable_name_menu(cub3d->mlx, menu);
		enable_level_menu(&cub3d->level_menu);
		cub3d->state = STATE_LEVEL;
		cub3d->speedrun = FALSE;
		menu->changed = FALSE;
		return (1);
	}
	if (cub3d->keys.enter)
	{
		submit_name(cub3d, menu);
		disable_name_menu(cub3d->mlx, menu);
		enable_leaderboard(cub3d, &cub3d->leaderboard);
		cub3d->state = STATE_LEADERBOARD;
		cub3d->speedrun = FALSE;
		menu->changed = FALSE;
		return (1);
	}
	if (cub3d->keys.backspace)
		handle_backspace(cub3d, menu);
	else if (menu->current < MAX_NAME_LENGTH)
		get_letter(cub3d, menu);
	menu->changed = FALSE;
	return (0);
}
