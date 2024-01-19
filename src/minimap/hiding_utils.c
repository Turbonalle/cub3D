/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hiding_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slampine <slampine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:39:52 by slampine          #+#    #+#             */
/*   Updated: 2024/01/19 13:28:27 by slampine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	get_door_key_color(t_cub3d *cub3d, int index)
{
	if (index == 0)
		return (cub3d->minimap.color_key_1);
	else if (index == 1)
		return (cub3d->minimap.color_key_2);
	else if (index == 2)
		return (cub3d->minimap.color_key_3);
	else if (index == 3)
		return (cub3d->minimap.color_key_4);
	else
		return (cub3d->minimap.color_door_open);
}

int	next_to_hidden(t_cub3d *cub3d, int row, int column)
{
	if (cub3d->level->map[row][column] == '0')
		return (0);
	if (ft_strchr("hr", cub3d->level->map[row - 1][column]))
		return (1);
	if (ft_strchr("hr", cub3d->level->map[row + 1][column]))
		return (1);
	if (ft_strchr("hr", cub3d->level->map[row][column - 1]))
		return (1);
	if (ft_strchr("hr", cub3d->level->map[row][column + 1]))
		return (1);
	return (0);
}

int	get_hidden_color(t_cub3d *cub3d, int index, int row, int column)
{
	if (next_to_hidden(cub3d, row, column))
		return (cub3d->minimap.color_wall);
	if (cub3d->speedrun == 1)
		return (cub3d->minimap.color_door_locked);
	else
	{
		if (index == 0)
			return (cub3d->minimap.color_key_1);
		else if (index == 1)
			return (cub3d->minimap.color_key_2);
		else if (index == 2)
			return (cub3d->minimap.color_key_3);
		else if (index == 3)
			return (cub3d->minimap.color_key_4);
		else
			return (cub3d->minimap.color_door_open);
	}
}

void	draw_shroom(t_cub3d *cub3d, int row, int column, t_vector pos)
{
	if (cub3d->level->map[row][column] == 'm')
	{
		draw_circle(cub3d->minimap.img,
			pos,
			cub3d->minimap.tile_size / 2,
			MINIMAP_COLOR_SHROOM);
	}
}
