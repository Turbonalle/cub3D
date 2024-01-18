/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collison_utils_additional.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:39:24 by slampine          #+#    #+#             */
/*   Updated: 2024/01/18 09:45:51 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_pos(t_cub3d *cub3d, int pos_y, int pos_x)
{
	if ((cub3d->level->map[pos_y][pos_x] == WALL
		|| is_locked_door(cub3d, pos_y, pos_x) == TRUE))
		return (1);
	return (0);
}
