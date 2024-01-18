/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:57:09 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 14:57:24 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	free_prev_level_menu(t_level_menu *menu, int i, int j)
{
	while (i > 0)
	{
		mlx_delete_texture(menu->minilevels[--i].number.texture);
	}
	mlx_delete_texture(menu->title.texture);
	if (j > 0)
		mlx_delete_texture(menu->back.texture);
	if (j > 1)
		mlx_delete_texture(menu->back_hover.texture);
	if (j > 2)
		mlx_delete_texture(menu->leaderboard.texture);
	if (j > 3)
		mlx_delete_texture(menu->leaderboard_hover.texture);
	return (FAIL);
}
