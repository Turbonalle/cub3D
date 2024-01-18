/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_leaderboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:21:12 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:51:26 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	update_leaderboard(t_cub3d *cub3d, t_leaderboard *board)
{
	if (hover_image(cub3d, board->back.img))
	{
		board->back_hover.img->instances[0].enabled = TRUE;
		board->back.img->instances[0].enabled = FALSE;
	}
	else
	{
		board->back_hover.img->instances[0].enabled = FALSE;
		board->back.img->instances[0].enabled = TRUE;
	}
}
